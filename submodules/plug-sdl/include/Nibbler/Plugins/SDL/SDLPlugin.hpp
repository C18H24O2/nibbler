/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDLPlugin.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:53:57 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/28 11:34:03 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Nibbler/Plugin/PluginSystem.hpp>

namespace Nibbler::Plugins::SDL
{

using namespace Nibbler::Plugin;
using Nibbler::Util::Identifier;

struct SDLPlugin: public Plugin
{
	void Init(PluginSystem& system) override;
	void Shutdown() override;

	static constexpr auto id = *Identifier::From("nibbler", "sdl");
	static constexpr PluginMetadata metadata{
		.name = "SDL",
		.author = "kiroussa",
		.version = "0.0.1",
		.description = "Provides client functionality (Window, Renderer, etc.) using the SDL3 library"
	};
};

}; // namespace Nibbler::Plugins::SDL
