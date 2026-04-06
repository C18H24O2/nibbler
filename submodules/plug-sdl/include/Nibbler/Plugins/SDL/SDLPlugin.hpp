/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDLPlugin.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:53:57 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/06 14:15:25 by kiroussa         ###   ########.fr       */
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
	bool Init(PluginSystem& system) noexcept override;
	void Shutdown(PluginSystem& system) noexcept override;

	constexpr PluginMetadata GetMetadata() const noexcept override
	{
		return metadata;
	}

	static constexpr PluginMetadata metadata{
		.id = *Identifier::From("nibbler", "sdl"),
		.name = "SDL",
		.author = "kiroussa",
		.version = "0.0.1",
		.description = "Provides client functionality (Window, Renderer, etc.) using the SDL3 library"
	};
};

}; // namespace Nibbler::Plugins::SDL
