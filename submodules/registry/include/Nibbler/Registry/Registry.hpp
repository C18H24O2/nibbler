/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Registry.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 17:59:36 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/27 19:25:37 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Nibbler/Util/Canonical.hpp"
#include <Nibbler/Registry/ResourceKey.hpp>
#include <Nibbler/Registry/RegistryBase.hpp>
#include <Nibbler/Util/Identifier.hpp>

#include <shared_mutex>
#include <mutex>
#include <unordered_map>
#include <vector>
#include <memory>
#include <optional>
#include <expected>
#include <typeindex>
#include <ranges>
#include <functional>

namespace Nibbler::Registry
{

using Nibbler::Util::Identifier;

enum class RegistryError
{
	NotFound,
	InvalidId,
	AlreadyRegistered,
};

template<typename T>
class Registry : public RegistryBase
{
private:
	Registry() noexcept = delete;
	DEFAULT_CANONICAL_MEMBERS(Registry)
public:
	Registry(Identifier location) : RegistryBase(std::move(location), std::type_index(typeid(T))) {}

	[[nodiscard]] constexpr std::expected<ResourceKey<T>, RegistryError> Register(Identifier location, std::shared_ptr<T> value) noexcept
	{
		std::unique_lock lock(mutex);

		if (keyToId.contains(location))
			return std::unexpected(RegistryError::AlreadyRegistered);

		int id = static_cast<int>(idToKey.size());

		ResourceKey<T> resourceKey{
			.registry = RegistryKey<T>{ .location = Location() },
			.location = location
		};

		idToKey.push_back(location);
		keyToId.emplace(location, id);
		keyToValue.emplace(location, std::move(value));

		return resourceKey;
	}

	[[nodiscard]] constexpr std::expected<void, RegistryError> Unregister(const Identifier& location) noexcept
	{
		std::unique_lock lock(mutex);

		auto it = keyToId.find(location);
		if (it == keyToId.end())
			return std::unexpected(RegistryError::NotFound);

		int removedId = it->second;

		keyToId.erase(it);
		keyToValue.erase(location);
		idToKey.erase(idToKey.begin() + removedId);

		for (auto& [key, id] : keyToId)
		{
			if (id > removedId)
				--id;
		}

		return {};
	}

	[[nodiscard]] constexpr std::expected<std::shared_ptr<T>, RegistryError> Get(const Identifier& location) const noexcept
	{
		std::shared_lock lock(mutex);

		auto it = keyToValue.find(location);
		if (it == keyToValue.end())
			return std::unexpected(RegistryError::NotFound);

		return it->second;
	}

	[[nodiscard]] constexpr std::expected<std::shared_ptr<T>, RegistryError> GetById(int id) const noexcept
	{
		std::shared_lock lock(mutex);

		if (id < 0 || id >= static_cast<int>(idToKey.size()))
			return std::unexpected(RegistryError::InvalidId);

		auto it = keyToValue.find(idToKey[id]);
		if (it == keyToValue.end())
			return std::unexpected(RegistryError::NotFound);

		return it->second;
	}

	[[nodiscard]] constexpr std::expected<int, RegistryError> GetId(const Identifier& location) const noexcept
	{
		std::shared_lock lock(mutex);

		auto it = keyToId.find(location);
		if (it == keyToId.end())
			return std::unexpected(RegistryError::NotFound);

		return it->second;
	}

	[[nodiscard]] constexpr std::expected<Identifier, RegistryError> GetKey(int id) const noexcept
	{
		std::shared_lock lock(mutex);

		if (id < 0 || id >= static_cast<int>(idToKey.size()))
			return std::unexpected(RegistryError::InvalidId);

		return idToKey[id];
	}

	[[nodiscard]] constexpr bool Contains(const Identifier& location) const noexcept
	{
		std::shared_lock lock(mutex);
		return keyToId.contains(location);
	}

	[[nodiscard]] constexpr std::size_t Size() const noexcept
	{
		std::shared_lock lock(mutex);
		return idToKey.size();
	}

	[[nodiscard]] constexpr std::vector<std::pair<Identifier, std::shared_ptr<T>>> Entries() const
	{
		std::shared_lock lock(mutex);

		std::vector<std::pair<Identifier, std::shared_ptr<T>>> result;
		result.reserve(idToKey.size());

		for (const auto& key : idToKey)
			result.emplace_back(key, keyToValue.at(key));

		return result;
	}

private:
	mutable std::shared_mutex mutex;

	std::vector<Identifier> idToKey;
	std::unordered_map<Identifier, int> keyToId;
	std::unordered_map<Identifier, std::shared_ptr<T>> keyToValue;
};

}
