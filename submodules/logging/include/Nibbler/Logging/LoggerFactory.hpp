/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoggerFactory.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 23:12:24 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/25 04:57:03 by kiroussa         ###   ########.fr       */
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

	static LoggerFactory& instance();

	void addConfigurator(ConfigureFn fn);
	void reconfigure();

	void registerLogger(Logger& logger);
	void unregisterLogger(Logger& logger);

	Logger* get(std::string_view name);

	// This is used to check whether the LoggerFactory's singleton has been destroyed
	// by the dynamic loader and prevent Loggers from trying to access it, causing,
	// among other things, a segmentation fault. :3
	static bool isAlive() noexcept;

private:
	LoggerFactory() = default;
	~LoggerFactory() noexcept;

	void applyConfigurators(Logger& logger);

	std::shared_mutex registryMutex;
	std::vector<Logger*> loggers;
	std::vector<ConfigureFn> globalConfigurators;

    inline static std::atomic<bool> alive{true};
};

}; // namespace Nibbler::Logging
