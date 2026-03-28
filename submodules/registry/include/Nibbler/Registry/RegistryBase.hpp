/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RegistryBase.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 17:51:39 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/27 17:53:19 by kiroussa         ###   ########.fr       */
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
	RegistryBase(Identifier location, std::type_index typeIndex);
	virtual ~RegistryBase() = default;
 
	RegistryBase(const RegistryBase&) = delete;
	RegistryBase& operator=(const RegistryBase&) = delete;
	RegistryBase(RegistryBase&&) = delete;
	RegistryBase& operator=(RegistryBase&&) = delete;
 
	[[nodiscard]] const Identifier& Location() const noexcept;
	[[nodiscard]] std::type_index TypeIndex() const noexcept;
 
private:
	Identifier location;
	std::type_index typeIndex;
};
 
}; // namespace Nibbler::Registry
