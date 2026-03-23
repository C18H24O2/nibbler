/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoggerFactory.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 00:22:59 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/23 00:25:29 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Nibbler/Logging/Logger.hpp>
#include <Nibbler/Logging/LoggerFactory.hpp>

namespace Nibbler::Logging
{

LoggerFactory& LoggerFactory::instance()
{
	static LoggerFactory instance;
	return instance;
}

void LoggerFactory::addGlobalConfigurator(ConfigureFn fn)
{
	std::unique_lock lock(registryMutex);
	globalConfigurators.push_back(std::move(fn));
}
 
void LoggerFactory::addConfigurator(std::string_view prefix, ConfigureFn fn)
{
	std::unique_lock lock(registryMutex);
	prefixConfigurators.push_back({std::string(prefix), std::move(fn)});
}
 
void LoggerFactory::reconfigure()
{
	std::unique_lock lock(registryMutex);
	for (auto& [name, logger] : loggers)
		applyConfigurators(*logger);
}
 
void LoggerFactory::registerLogger(Logger& logger)
{
	std::unique_lock lock(registryMutex);
	loggers[std::string(logger.name())] = &logger;
	applyConfigurators(logger);
}
 
void LoggerFactory::unregisterLogger(Logger& logger)
{
	std::unique_lock lock(registryMutex);
	loggers.erase(std::string(logger.name()));
}
 
Logger* LoggerFactory::get(std::string_view name)
{
	std::shared_lock lock(registryMutex);
	auto it = loggers.find(std::string(name));
	return it != loggers.end() ? it->second : nullptr;
}
 
void LoggerFactory::setLevel(std::string_view prefix, LogLevel logLevel)
{
	std::shared_lock lock(registryMutex);
	for (auto& [name, logger] : loggers)
		if (name.starts_with(prefix))
			logger->setLevel(logLevel);
}
 
void LoggerFactory::applyConfigurators(Logger& logger)
{
	for (auto& fn : globalConfigurators)
		fn(logger);
 
	for (auto& [prefix, fn] : prefixConfigurators)
		if (logger.name().starts_with(prefix))
			fn(logger);
}

}; // namespace Nibbler::Logging
