/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LaunchArgument.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 03:05:51 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/09 03:41:23 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <array>
#include <string>
#include <string_view>

struct LaunchArgument
{
	char shortName;
	std::string_view longName;
	std::string_view description;
};
//TODO: template function that takes a <*>Options struct and complements the parsing
//can it be done? the type is parsed at runtime so there needs to be a link from enum to function

