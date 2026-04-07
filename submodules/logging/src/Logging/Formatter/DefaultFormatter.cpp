/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DefaultFormatter.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 02:24:01 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/07 03:29:32 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <chrono>
#include <filesystem>
#include <Nibbler/Logging/Logger.hpp>
#include <Nibbler/Logging/Formatter/DefaultFormatter.hpp>

namespace Nibbler::Logging
{

// [10:42:42] [launcher/argparse] (INFO/main.cpp:56) Launching mode: standalone

std::string DefaultFormatter::Format(const Logger& logger, const LogRecord& record) noexcept
{
	auto filename = std::filesystem::path(record.location.file_name()).filename().string();
	if (record.marker)
		return std::format("[{:%H:%M:%S}] [{}/{}] ({}/{}:{}) {}", std::chrono::floor<std::chrono::seconds>(record.time), logger.GetNibblerModule(), record.marker->GetFullName(), record.level.GetName(), filename, record.location.line(), record.message);
	else
		return std::format("[{:%H:%M:%S}] [{}] ({}/{}:{}) {}", std::chrono::floor<std::chrono::seconds>(record.time), logger.GetNibblerModule(), record.level.GetName(), filename, record.location.line(), record.message);

	// std::size_t longest = 0;
	// for (auto& logger : LoggerFactory::Instance().GetAll())
	// 	longest = std::max(longest, logger->GetNibblerModule().size());
	//
	// if (record.marker)
	// 	return std::format("[{:%H:%M:%S}] {:>{}}/{} ({}/{}:{}) {}", std::chrono::floor<std::chrono::seconds>(record.time), logger.GetNibblerModule(), longest, record.marker->GetFullName(), record.level.GetName(), filename, record.location.line(), record.message);
	// else
	// 	return std::format("[{:%H:%M:%S}] {:>{}} ({}/{}:{}) {}", std::chrono::floor<std::chrono::seconds>(record.time), logger.GetNibblerModule(), longest, record.level.GetName(), filename, record.location.line(), record.message);
}

}; // namespace Nibbler::Logging
