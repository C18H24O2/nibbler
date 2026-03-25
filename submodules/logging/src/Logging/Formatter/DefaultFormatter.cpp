/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DefaultFormatter.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 02:24:01 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/25 04:51:53 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <chrono>
#include <filesystem>
#include <Nibbler/Logging/Logger.hpp>
#include <Nibbler/Logging/Formatter/DefaultFormatter.hpp>

namespace Nibbler::Logging
{

// [10:42:42] [launcher/argparse] (INFO/main.cpp:56) Launching mode: standalone

std::string DefaultFormatter::format(const Logger& logger, const LogRecord& record) noexcept
{
	auto filename = std::filesystem::path(record.location.file_name()).filename().string();
	if (record.marker)
		return std::format("[{:%H:%M:%S}] [{}/{}] ({}/{}:{}) {}", std::chrono::floor<std::chrono::seconds>(record.time), logger.getNibblerModule(), record.marker->getFullName(), record.level.getName(), filename, record.location.line(), record.message);
	else
		return std::format("[{:%H:%M:%S}] [{}] ({}/{}:{}) {}", std::chrono::floor<std::chrono::seconds>(record.time), logger.getNibblerModule(), record.level.getName(), filename, record.location.line(), record.message);
}

}; // namespace Nibbler::Logging
