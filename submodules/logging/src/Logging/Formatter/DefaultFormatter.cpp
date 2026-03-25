/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DefaultFormatter.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 02:24:01 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/25 03:49:18 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <chrono>
#include <Nibbler/Logging/Logger.hpp>
#include <Nibbler/Logging/Formatter/DefaultFormatter.hpp>

namespace Nibbler::Logging
{

// [10:42:42] [launcher/argparse] (INFO/main.cpp:56) Launching mode: standalone

std::string DefaultFormatter::format(const Logger& logger, const LogRecord& record) noexcept
{
	auto filename = std::string(record.location.file_name());
	size_t sub;
	if ((sub = filename.find("/src/")) != std::string_view::npos)
		filename = filename.substr(sub + 5);
	else if ((sub = filename.find("/include/")) != std::string_view::npos)
		filename = filename.substr(sub + 9);

	if (record.marker)
		return std::format("[{:%H:%M:%S}] [{}/{}] ({}/{}:{}) {}", std::chrono::floor<std::chrono::seconds>(record.time), logger.getNibblerModule(), record.marker->getFullName(), record.level.getName(), filename, record.location.line(), record.message);
	else
		return std::format("[{:%H:%M:%S}] [{}] ({}/{}:{}) {}", std::chrono::floor<std::chrono::seconds>(record.time), logger.getNibblerModule(), record.level.getName(), filename, record.location.line(), record.message);
}

}; // namespace Nibbler::Logging
