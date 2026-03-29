/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDLPlugin.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:53:24 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/28 13:31:18 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Nibbler/Logging/Logger.hpp>
#include <Nibbler/Plugins/SDL/SDLPlugin.hpp>

#include <Nibbler/Client/Window/WindowProvider.hpp>
#include <Nibbler/Registry/Registries.hpp>

namespace Nibbler::Plugins::SDL
{

Logging::Logger logger("Plugins::SDL");

void SDLPlugin::Init(PluginSystem& system)
{
	(void) system;
	logger.Info().Emit("Initializing SDL plugin");

	// Registries::Register(WindowProvider::REGISTRY_KEY, SDLWindowProvider::ID, std::make_unique<SDLWindowProvider>());
}

void SDLPlugin::Shutdown()
{
	logger.Info().Emit("Shutting down...");
}

};

PLUGIN_DECLARE(Nibbler::Plugins::SDL::SDLPlugin)
