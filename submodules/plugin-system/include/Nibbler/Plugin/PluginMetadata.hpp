/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PluginMetadata.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:50:21 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/28 00:52:58 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string_view>

namespace Nibbler::Plugin
{

struct PluginMetadata
{
	std::string_view name;
	std::string_view author;
	std::string_view version;
	std::string_view description;
};

}; // namespace Nibbler::Plugin
