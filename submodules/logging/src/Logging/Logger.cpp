/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 00:17:00 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/25 16:36:19 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <filesystem>
#include <Nibbler/Logging/Logger.hpp>
#include <Nibbler/Logging/LoggerFactory.hpp>

namespace Nibbler::Logging
{
 
Logger::Logger(std::string_view name, std::source_location loc)
{
	this->name = name;
	this->loc = loc;
	auto filepath = std::filesystem::path(loc.file_name());

	std::string nibblerModule = "unknown module";
	bool next = false;
	for (auto& part : filepath.relative_path())
	{
		if (part == "submodules")
			next = true;
		else if (next)
		{
			nibblerModule = part.string();
			break;
		}
	}
	this->nibblerModule = nibblerModule;

	LoggerFactory::Instance().RegisterLogger(*this);
}
 
Logger::~Logger() noexcept
{
	if (LoggerFactory::IsAlive())
		LoggerFactory::Instance().UnregisterLogger(*this);
}

std::string_view Logger::GetName() const noexcept
{
	return name;
}
 
std::source_location Logger::GetLocation() const noexcept
{
	return loc;
}

std::string_view Logger::GetNibblerModule() const noexcept
{
	return nibblerModule;
}
 
void Logger::AddSink(std::shared_ptr<ISink> sink)
{
	std::unique_lock lock(sinkMutex);
	sinks.push_back(std::move(sink));
}
 
void Logger::ClearSinks()
{
	std::unique_lock lock(sinkMutex);
	sinks.clear();
}
 
void Logger::SetLevel(LogLevel logLevel) noexcept
{
	minLogLevel.store(logLevel, std::memory_order_relaxed);
}
 
LogLevel Logger::GetLevel() const noexcept
{
	return minLogLevel.load(std::memory_order_relaxed);
}
 
void Logger::Flush() noexcept
{
	std::shared_lock lock(sinkMutex);
	for (auto& sink : sinks)
		sink->Flush();
}

Logger::LogProxy::CallSite Logger::LogProxy::operator()(std::source_location loc) noexcept
{
	return { logger, level, loc };
}

Logger::LogProxy::CallSite Logger::LogProxy::operator()(const LogMarker& marker, std::source_location loc) noexcept
{
	return { logger, level, loc, const_cast<LogMarker*>(&marker) };
}

}; // namespace Nibbler::Logging
