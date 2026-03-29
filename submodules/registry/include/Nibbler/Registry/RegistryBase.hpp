/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RegistryBase.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 17:51:39 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/29 08:40:57 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
 
#include <typeindex>

#include <Nibbler/Util/Identifier.hpp>
#include <Nibbler/Util/NonCopyable.hpp>
#include <Nibbler/Util/NonMovable.hpp>
 
namespace Nibbler::Registry
{

using namespace Nibbler::Util;
 
class RegistryBase: public NonCopyable, public NonMovable
{
public:
	constexpr RegistryBase(Identifier location, std::type_index typeIndex) noexcept
		: location(std::move(location)), typeIndex(typeIndex) {}
	virtual ~RegistryBase() = default;
 
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
