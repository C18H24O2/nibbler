/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RegistryKey.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:52:55 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/27 17:50:44 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
 
#include <Nibbler/Util/Identifier.hpp>
#include <compare>
#include <functional>
 
namespace Nibbler::Registry
{

using Nibbler::Util::Identifier;
 
template<typename T>
struct RegistryKey
{
	Identifier location;
 
	[[nodiscard]] constexpr auto operator<=>(const RegistryKey<T>& other) const noexcept
	{
		return location <=> other.location;
	}
 
	[[nodiscard]] constexpr bool operator==(const RegistryKey<T>& other) const noexcept
	{
		return location == other.location;
	}
};

}; // namespace Nibbler::Registry

template<typename T>
struct std::hash<Nibbler::Registry::RegistryKey<T>>
{
	[[nodiscard]] constexpr std::size_t operator()(const Nibbler::Registry::RegistryKey<T>& key) const noexcept
	{
		return std::hash<Nibbler::Util::Identifier>{}(key.location);
	}
};
