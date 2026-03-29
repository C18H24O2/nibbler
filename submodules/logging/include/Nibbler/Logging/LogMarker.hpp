/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LogMarker.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 02:52:20 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/28 21:15:57 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <string_view>

#include <Nibbler/Util/Canonical.hpp>
 
namespace Nibbler::Logging
{

struct LogMarker
{
	[[nodiscard]] constexpr std::string GetFullName(std::string_view separator = ".") const noexcept
	{
		if (!parent)
			return std::string(name);
		return parent->GetFullName(separator) + std::string(separator) + std::string(name);
	}

	const std::string_view name;
	const LogMarker* parent = nullptr;
};

}; // namespace Nibbler::Logging
