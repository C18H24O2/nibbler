/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LogMarker.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 02:57:12 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/25 03:09:15 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Nibbler/Logging/LogMarker.hpp>

namespace Nibbler::Logging
{

std::string LogMarker::getFullName(std::string_view separator) const noexcept
{
	if (!parent)
		return std::string(name);
	return parent->getFullName(separator) + std::string(separator) + std::string(name);
}

}; // namespace Nibbler::Logging
