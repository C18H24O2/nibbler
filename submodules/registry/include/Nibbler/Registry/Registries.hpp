/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Registries.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:54:05 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/06 13:36:36 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
  
#include <unordered_map>
#include <memory>
#include <shared_mutex>
#include <mutex>
#include <expected>
#include <typeindex>

#include <Nibbler/Registry/Registry.hpp>
 
namespace Nibbler::Registry
{

using Nibbler::Util::Identifier;
 
class Registries
{
public:
	Registries() = delete;
 
	template<typename T>
	[[nodiscard]] static constexpr Registry<T>& GetRegistry(const RegistryKey<T>& key) noexcept
	{
		std::unique_lock lock(Mutex());

		auto it = Store().find(key.location);
		if (it == Store().end())
		{
			auto reg = std::make_unique<Registry<T>>(key.location);
			auto& ref = *reg;
			Store().emplace(key.location, std::move(reg));
			return ref;
		}

		return *static_cast<Registry<T>*>(it->second.get());
	}
 
	[[nodiscard]] static constexpr std::expected<void, RegistryError> RemoveRegistry(Identifier location) noexcept
	{
		std::unique_lock lock(Mutex());
 
		if (!Store().contains(location))
			return std::unexpected(RegistryError::NotFound);
 
		Store().erase(location);
		return {};
	}
 
	[[nodiscard]] static constexpr bool Contains(Identifier location) noexcept
	{
		std::shared_lock lock(Mutex());
		return Store().contains(location);
	}
 
	[[nodiscard]] static std::size_t RegistryCount() noexcept
	{
		std::shared_lock lock(Mutex());
		return Store().size();
	}
 
	template<typename T, typename U = T>
	requires std::derived_from<U, T>
	[[nodiscard]] static std::expected<ResourceKey<T>, RegistryError> Register(
		RegistryKey<T> registryKey,
		Identifier location,
		std::shared_ptr<U> value
	) noexcept {
		return GetRegistry<T>(registryKey).Register(location, std::move(value));
	}

	template <typename T>
	static std::expected<void, RegistryError> Unregister(
		RegistryKey<T> registryKey,
		const Identifier& location
	) noexcept {
		return GetRegistry<T>(registryKey).Unregister(location);
	}
private:
	static std::unordered_map<Identifier, std::unique_ptr<RegistryBase>>& Store() noexcept
	{
		static std::unordered_map<Identifier, std::unique_ptr<RegistryBase>> store;
		return store;
	}
 
	static std::shared_mutex& Mutex() noexcept
	{
		static std::shared_mutex mutex;
		return mutex;
	}
};

}; // namespace Nibbler::Registry
