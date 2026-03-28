/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceKey.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 17:49:22 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/27 19:13:13 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <string_view>

#include <Nibbler/Registry/RegistryKey.hpp>

namespace Nibbler::Registry
{

template<typename T>
struct ResourceKey
{
	RegistryKey<T> registry;
	Nibbler::Util::Identifier location;
 
	[[nodiscard]] constexpr auto operator<=>(const ResourceKey<T>& other) const noexcept
	{
		auto cmp = registry <=> other.registry; 
		if (cmp == std::strong_ordering::equal)
			cmp = location <=> other.location;
		return cmp;
	}
 
	[[nodiscard]] constexpr bool operator==(const ResourceKey<T>& other) const noexcept
	{
		return registry == other.registry && location == other.location;
	}
};

}; // namespace Nibbler::Registry

template<typename T>
struct std::hash<Nibbler::Registry::ResourceKey<T>>
{
	[[nodiscard]] constexpr std::size_t operator()(const Nibbler::Registry::ResourceKey<T>& key) const noexcept
	{
		std::size_t h1 = std::hash<Nibbler::Util::Identifier>{}(key.registry.location);
		std::size_t h2 = std::hash<Nibbler::Util::Identifier>{}(key.location);
		return h1 ^ (h2 << 32 | h2 >> 32);
	}
};
