/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoggerFactory.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 00:22:59 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/25 16:35:35 by kiroussa         ###   ########.fr       */
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

bool LoggerFactory::IsAlive() noexcept
{
	return alive;
}

LoggerFactory& LoggerFactory::Instance()
{
	static LoggerFactory instance;
	return instance;
}

void LoggerFactory::AddConfigurator(ConfigureFn fn)
{
	std::unique_lock lock(registryMutex);
	globalConfigurators.push_back(std::move(fn));
}
 
void LoggerFactory::Reconfigure()
{
	std::unique_lock lock(registryMutex);
	for (auto& logger : loggers)
		ApplyConfigurators(*logger);
}
 
void LoggerFactory::RegisterLogger(Logger& logger)
{
	std::unique_lock lock(registryMutex);
	loggers.push_back(&logger);
	ApplyConfigurators(logger);
}
 
void LoggerFactory::UnregisterLogger(Logger& logger)
{
	std::unique_lock lock(registryMutex);
	loggers.erase(std::remove(loggers.begin(), loggers.end(), &logger), loggers.end());
}
 
Logger* LoggerFactory::Get(std::string_view name)
{
	std::shared_lock lock(registryMutex);
	for (auto& logger : loggers)
		if (logger->GetName() == name)
			return logger;
	return nullptr;
}
 
void LoggerFactory::ApplyConfigurators(Logger& logger)
{
	for (auto& fn : globalConfigurators)
		fn(logger);
}

}; // namespace Nibbler::Logging
