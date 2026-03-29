/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entrypoint.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 04:10:59 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/29 08:48:21 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Nibbler/Logging/Logger.hpp>
#include <Nibbler/Logging/LoggerFactory.hpp>
#include <Nibbler/Logging/LogLevel.hpp>
#include <Nibbler/Registry/Registries.hpp>
#include <Nibbler/Client/Window/WindowProvider.hpp>
#include <Nibbler/Standalone/entrypoint.hpp>

namespace Nibbler::Standalone
{

using namespace Nibbler::Registry;

Logging::Logger logger("entrypoint");

int Entrypoint(Launcher::LaunchOptions& options)
{
	(void)options;
	logger.Debug().Emit("Standalone mode entrypoint");

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
