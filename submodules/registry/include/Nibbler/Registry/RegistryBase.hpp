/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RegistryBase.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 17:51:39 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/28 11:42:13 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
 
#include <typeindex>

#include <Nibbler/Util/Identifier.hpp>
 
namespace Nibbler::Registry
{

using Nibbler::Util::Identifier;
 
class RegistryBase
{
public:
	constexpr RegistryBase(Identifier location, std::type_index typeIndex) noexcept
		: location(std::move(location)), typeIndex(typeIndex) {}
	virtual ~RegistryBase() = default;
 
	RegistryBase(const RegistryBase&) = delete;
	RegistryBase& operator=(const RegistryBase&) = delete;
	RegistryBase(RegistryBase&&) = delete;
	RegistryBase& operator=(RegistryBase&&) = delete;
 
	[[nodiscard]] constexpr const Identifier& Location() const noexcept
	{
		return location;
	}

	[[nodiscard]] constexpr std::type_index TypeIndex() const noexcept
	{
		return typeIndex;
	}
 
private:
	Identifier location;
	std::type_index typeIndex;
};
 
}; // namespace Nibbler::Registry
