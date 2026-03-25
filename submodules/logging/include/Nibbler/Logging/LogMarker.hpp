/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LogMarker.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 02:52:20 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/25 16:35:35 by kiroussa         ###   ########.fr       */
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
	[[nodiscard]] std::string GetFullName(std::string_view separator = ".") const noexcept;

	const std::string_view name;
	const LogMarker* parent = nullptr;
};

}; // namespace Nibbler::Logging
