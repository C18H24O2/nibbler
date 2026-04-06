/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entrypoint.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 04:10:59 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/06 14:15:04 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Nibbler/Logging/Logger.hpp>
#include <Nibbler/Registry/Registries.hpp>
#include <Nibbler/Client/Window/WindowProvider.hpp>
#include <Nibbler/Plugin/PluginSystem.hpp>
#include <Nibbler/Plugin/Discoverer/FilesystemPluginDiscoverer.hpp>
#include <Nibbler/Plugin/Loader/DlPluginLoader.hpp>
#include <Nibbler/Standalone/entrypoint.hpp>

namespace Nibbler::Standalone
{

using namespace Nibbler::Registry;

Logging::Logger logger("entrypoint");

int Entrypoint(Launcher::LaunchOptions& options)
{
	logger.Debug().Emit("Standalone mode entrypoint");

	Launcher::StandaloneOptions* opts = std::get_if<Launcher::StandaloneOptions>(&options.modeOptions);
	if (!opts)
	{
		logger.Fatal().Emit("Invalid options");
		return 1;
	}
	if (opts->width <= 0 || opts->height <= 0 || opts->width > 100 || opts->height > 100)
	{
		logger.Fatal().Emit("Invalid game width / height");
		return 1;
	}

	// Initialize the plugin system
	Plugin::PluginSystem pluginSystem;
	pluginSystem.AddDiscoverer(std::make_unique<Plugin::FilesystemPluginDiscoverer>(".", true));
	pluginSystem.AddLoader(std::make_unique<Plugin::DlPluginLoader>());
	pluginSystem.LoadPlugins();
	
	auto& reg = Registries::GetRegistry(Client::Window::WindowProvider::REGISTRY_KEY);
	auto entries = reg.Entries();
	if (entries.empty())
	{
		logger.Error().Emit("No window providers found");
		return 1;
	}
	for (const auto& [id, provider] : entries)
	{
		logger.Debug().Emit("Found window provider: {}", id);
	}

	// Steps:
	// - Initialize the plugin system
	// - Setup the internal server
	// - Setup the client window
	// - Profit
	return 0;
}

}; // namespace Nibbler
