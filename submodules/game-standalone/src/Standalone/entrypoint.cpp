/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entrypoint.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 04:10:59 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/27 20:18:04 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Nibbler/Standalone/entrypoint.hpp>
#include <Nibbler/Logging/Logger.hpp>
#include <Nibbler/Logging/LoggerFactory.hpp>
#include <Nibbler/Logging/LogLevel.hpp>

namespace Nibbler::Standalone
{

Logging::Logger logger("entrypoint");

void Entrypoint(Launcher::LaunchOptions& options)
{
	(void)options;
	logger.Debug().Emit("Standalone mode entrypoint");



	// Steps:
	// - Setup the internal server
	// - Setup the client window
	// - Profit
}

}; // namespace Nibbler
