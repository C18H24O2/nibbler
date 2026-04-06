/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDLPlugin.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:53:24 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/06 14:21:01 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL3/SDL.h>

#include <Nibbler/Logging/Logger.hpp>
#include <Nibbler/Registry/Registries.hpp>

#include <Nibbler/Plugins/SDL/SDLWindowProvider.hpp>
#include <Nibbler/Plugins/SDL/SDLPlugin.hpp>

namespace Nibbler::Plugins::SDL
{

static constexpr char SDL_APP_NAME[] = "Nibbler";
static constexpr char SDL_APP_VERSION[] = "0.0.1-indev";
static constexpr char SDL_APP_IDENTIFIER[] = "dev.dynamicdispatch.nibbler";

static Logging::Logger logger("Plugins::SDL");
static bool sdlInitialized = false;

bool SDLPlugin::Init(PluginSystem& system) noexcept
{
	(void) system;
	logger.Info().Emit("Initializing SDL plugin");

	logger.Debug().Emit("Initializing SDL library");
	SDL_SetAppMetadata(SDL_APP_NAME, SDL_APP_VERSION, SDL_APP_IDENTIFIER);
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
	{
		logger.Error().Emit("Failed to initialize SDL library");
		return false;
	}
	sdlInitialized = true;

	//TODO: have a way to bulk register/unregister from registries
	// maybe DeferredRegistrar<T> requires RegistryKey<T> and
	//       DeferredRegistration<T> with Identifier, std::shared_ptr<T> provider lambda, and DeferredRegistrar ref as param
	if (!Registry::Registries::Register(Client::Window::WindowProvider::REGISTRY_KEY, SDLWindowProvider::ID, std::make_shared<SDLWindowProvider>()))
	{
		logger.Error().Emit("Failed to register SDLWindowProvider");
		return false;
	}

	return true;
}

void SDLPlugin::Shutdown(PluginSystem& system) noexcept
{
	logger.Info().Emit("Shutting down...");
	Registry::Registries::Unregister(Client::Window::WindowProvider::REGISTRY_KEY, SDLWindowProvider::ID);
	if (sdlInitialized)
		SDL_Quit();
}

};

PLUGIN_DECLARE(Nibbler::Plugins::SDL::SDLPlugin)
