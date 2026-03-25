/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoggerFactory.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 00:22:59 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/25 04:40:46 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Nibbler/Logging/Logger.hpp>
#include <Nibbler/Logging/LoggerFactory.hpp>

namespace Nibbler::Logging
{

LoggerFactory::~LoggerFactory() noexcept
{
	alive = false;
}

bool LoggerFactory::isAlive() noexcept
{
	return alive;
}

LoggerFactory& LoggerFactory::instance()
{
	static LoggerFactory instance;
	return instance;
}

void LoggerFactory::addConfigurator(ConfigureFn fn)
{
	std::unique_lock lock(registryMutex);
	globalConfigurators.push_back(std::move(fn));
}
 
void LoggerFactory::reconfigure()
{
	std::unique_lock lock(registryMutex);
	for (auto& logger : loggers)
		applyConfigurators(*logger);
}
 
void LoggerFactory::registerLogger(Logger& logger)
{
	std::unique_lock lock(registryMutex);
	loggers.push_back(&logger);
	applyConfigurators(logger);
}
 
void LoggerFactory::unregisterLogger(Logger& logger)
{
	std::unique_lock lock(registryMutex);
	loggers.erase(std::remove(loggers.begin(), loggers.end(), &logger), loggers.end());
}
 
Logger* LoggerFactory::get(std::string_view name)
{
	std::shared_lock lock(registryMutex);
	for (auto& logger : loggers)
		if (logger->getName() == name)
			return logger;
	return nullptr;
}
 
void LoggerFactory::applyConfigurators(Logger& logger)
{
	for (auto& fn : globalConfigurators)
		fn(logger);
}

}; // namespace Nibbler::Logging
