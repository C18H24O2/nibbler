/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LaunchArgument.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 03:05:51 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/10 17:45:54 by kiroussa         ###   ########.fr       */
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
