/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 01:17:09 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/28 01:22:59 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <libui/error.h>

namespace LibUI
{

enum class Error : std::uint16_t
{
	OK = UI_ERROR_OK,
	NULLPTR = UI_ERROR_NULLPTR,
	ALLOC = UI_ERROR_ALLOC,
	DRIVER = UI_ERROR_DRIVER,
};

}
