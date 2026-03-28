/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PluginContainer.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:50:11 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/28 00:52:50 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Nibbler/Plugin/PluginMetadata.hpp>

namespace Nibbler::Plugin
{

struct PluginContainer
{
	PluginMetadata metadata;
	// PluginHandle *handle;
};

}; // namespace Nibbler::Plugin
