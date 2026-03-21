/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LaunchArgument.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 03:05:51 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/21 21:03:08 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <string_view>
#include <variant>

template<typename T>
struct LaunchArgument
{
	char shortName;
	std::string_view longName;
	std::string_view description;

	using FieldPtr = std::variant<
        std::string T::*,
        int         T::*,
        bool        T::*,
        double      T::*
    >;

    FieldPtr fieldPtr;
};
