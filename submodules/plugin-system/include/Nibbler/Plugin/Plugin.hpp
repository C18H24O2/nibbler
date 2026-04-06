/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plugin.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:53:03 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/06 14:15:35 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <typeinfo>
#include <variant>

#include <Nibbler/Util/Identifier.hpp>
#include <Nibbler/Plugin/PluginMetadata.hpp>

namespace Nibbler::Plugin
{

using Nibbler::Util::Identifier;

class PluginSystem;

struct Plugin
{
	virtual ~Plugin() noexcept = default;

	virtual bool Init(PluginSystem& system) noexcept = 0;
	virtual void Shutdown(PluginSystem& system) noexcept = 0;
	virtual PluginMetadata GetMetadata() const noexcept = 0;
};

}; // namespace Nibbler::Plugin

#define PLUGIN_ENTRYPOINT_FUNC __Nibbler_GetPlugin
#define __STR(x) #x
#define __STR2(x) __STR(x)
#define PLUGIN_ENTRYPOINT_FUNC_NAME __STR2(PLUGIN_ENTRYPOINT_FUNC)
#define PLUGIN_DECLARE(T) \
	__attribute__((visibility("default"))) extern "C" \
	Nibbler::Plugin::Plugin* PLUGIN_ENTRYPOINT_FUNC() \
	{ \
		static T instance; \
		return &instance; \
	}
