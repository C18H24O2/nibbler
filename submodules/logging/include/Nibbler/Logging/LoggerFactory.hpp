/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoggerFactory.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 23:12:24 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/07 03:23:00 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <atomic>
#include <functional>
#include <shared_mutex>
#include <string_view>
#include <vector>

#include <Nibbler/Util/NonCopyable.hpp>
#include <Nibbler/Util/NonMovable.hpp>
#include <Nibbler/Logging/LogLevel.hpp>

namespace Nibbler::Logging
{

class Logger;

class LoggerFactory final : private Util::NonCopyable, private Util::NonMovable {
public:
	using ConfigureFn = std::function<void(Logger&)>;

	[[nodiscard]] static constexpr LoggerFactory& Instance() noexcept
	{
		static LoggerFactory instance;
		return instance;
	}

	constexpr void AddConfigurator(ConfigureFn fn) noexcept
	{
		std::unique_lock lock(registryMutex);
		globalConfigurators.push_back(std::move(fn));
	}

	constexpr void Reconfigure() noexcept
	{
		std::unique_lock lock(registryMutex);
		for (auto& logger : loggers)
			ApplyConfigurators(*logger);
	}

	constexpr void RegisterLogger(Logger& logger) noexcept
	{
		std::unique_lock lock(registryMutex);
		loggers.push_back(&logger);
		ApplyConfigurators(logger);
	}

	constexpr void UnregisterLogger(Logger& logger) noexcept
	{
		std::unique_lock lock(registryMutex);
		loggers.erase(std::remove(loggers.begin(), loggers.end(), &logger), loggers.end());
	}

	[[nodiscard]] const Logger* Get(std::string_view name) noexcept;

	[[nodiscard]] constexpr std::vector<Logger*>& GetAll() noexcept
	{
		return loggers;
	}

	// This is used to check whether the LoggerFactory's singleton has been destroyed
	// by the dynamic loader and prevent Loggers from trying to access it, causing,
	// among other things, a segmentation fault. :3
	[[nodiscard]] static constexpr bool IsAlive() noexcept
	{
		return alive;
	}

private:
	constexpr LoggerFactory() noexcept = default;
	constexpr ~LoggerFactory() noexcept
	{
		alive = false;
	}

	constexpr void ApplyConfigurators(Logger& logger) noexcept
	{
		for (auto& configurator : globalConfigurators)
			configurator(logger);
	}

	std::shared_mutex registryMutex;
	std::vector<Logger*> loggers;
	std::vector<ConfigureFn> globalConfigurators;

	inline static std::atomic<bool> alive{true};
};

}; // namespace Nibbler::Logging
