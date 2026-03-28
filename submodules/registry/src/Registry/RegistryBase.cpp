/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RegistryBase.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 17:52:17 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/27 17:56:44 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Nibbler/Registry/RegistryBase.hpp>
 
namespace Nibbler::Registry
{

using Nibbler::Util::Identifier;
 
RegistryBase::RegistryBase(Identifier loc, std::type_index ti)
	: location(std::move(loc)), typeIndex(ti) {}
 
const Identifier& RegistryBase::Location() const noexcept
{
	return location;
}
 
std::type_index RegistryBase::TypeIndex() const noexcept
{
	return typeIndex;
}
 
}; // namespace Nibbler::Registry
