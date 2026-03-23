/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 00:17:00 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/23 00:25:46 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <filesystem>
#include <Nibbler/Logging/Logger.hpp>
#include <Nibbler/Logging/LoggerFactory.hpp>

namespace Nibbler::Logging
{
 
Logger::Logger(std::source_location loc)
{
    auto stem = std::filesystem::path(loc.file_name()).stem().string();
    init(stem, loc.file_name());
}
 
Logger::Logger(std::string_view name, std::source_location loc)
{
    init(name, loc.file_name());
}
 
Logger::~Logger() noexcept
{
    LoggerFactory::instance().unregisterLogger(*this);
}
 
void Logger::init(std::string_view name, std::string_view file)
{
    module = name;
    sourceFile = file;
    LoggerFactory::instance().registerLogger(*this);
}
 
void Logger::addSink(std::shared_ptr<ISink> sink)
{
    std::unique_lock lock(sinkMutex);
    sinks.push_back(std::move(sink));
}
 
void Logger::clearSinks()
{
    std::unique_lock lock(sinkMutex);
    sinks.clear();
}
 
void Logger::setLevel(LogLevel logLevel) noexcept
{
    minLogLevel.store(logLevel, std::memory_order_relaxed);
}
 
LogLevel Logger::getLevel() const noexcept
{
    return minLogLevel.load(std::memory_order_relaxed);
}
 
void Logger::flush() noexcept
{
    std::shared_lock lock(sinkMutex);
    for (auto& sink : sinks)
        sink->flush();
}

}; // namespace Nibbler::Logging
