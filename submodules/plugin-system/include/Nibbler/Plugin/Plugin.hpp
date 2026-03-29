/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plugin.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:53:03 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/28 22:34:39 by kiroussa         ###   ########.fr       */
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

template<typename T>
concept PluginLike = requires(T t) {
	{ t.id } -> std::convertible_to<Identifier>;
	{ t.metadata } -> std::convertible_to<PluginMetadata>;
};

struct Plugin
{
	virtual ~Plugin() = default;

	virtual void Init(PluginSystem& system) = 0;
	virtual void Shutdown() = 0;
};

}; // namespace Nibbler::Plugin

#define PLUGIN_ENTRYPOINT_FUNC __Nibbler_GetPlugin
#define PLUGIN_DECLARE(T) \
	__attribute__((visibility("default"))) extern "C" \
	Nibbler::Plugin::Plugin* PLUGIN_ENTRYPOINT_FUNC() \
	{ \
		static T instance; \
		return &instance; \
	}
