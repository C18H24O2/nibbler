/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDLPlugin.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:53:24 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/28 11:37:41 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Nibbler/Logging/Logger.hpp>
#include <Nibbler/Plugins/SDL/SDLPlugin.hpp>

namespace Nibbler::Plugins::SDL
{

Logging::Logger logger("Plugins::SDL");

void SDLPlugin::Init(PluginSystem& system)
{
	logger.Info().Emit("Initializing SDL plugin");
}

void SDLPlugin::Shutdown()
{
	logger.Info().Emit("Shutting down...");
}

};

PLUGIN_DECLARE(Nibbler::Plugins::SDL::SDLPlugin)
