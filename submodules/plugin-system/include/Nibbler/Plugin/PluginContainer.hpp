/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PluginContainer.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:50:11 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/06 11:12:42 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <Nibbler/Plugin/PluginMetadata.hpp>
#include <Nibbler/Plugin/Plugin.hpp>

namespace Nibbler::Plugin
{

#if defined(_WIN32)
	using PluginHandle = HMODULE;
#else
	using PluginHandle = void *;
#endif

struct PluginContainer
{
	PluginMetadata metadata;
	Plugin *plugin;
	PluginHandle handle;
};

}; // namespace Nibbler::Plugin
