/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoggerFactory.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 23:12:24 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/25 03:51:24 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <functional>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <string_view>
#include <unordered_map>
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
	void addConfigurator(std::string_view prefix, ConfigureFn fn);
	void reconfigure();

	void registerLogger(Logger& logger);
	void unregisterLogger(Logger& logger);

	Logger* get(std::string_view name);

	void setLevel(std::string_view prefix, LogLevel logLevel);

private:
	LoggerFactory() = default;

	void applyConfigurators(Logger& logger);

	struct PrefixConfigurator {
		std::string prefix;
		ConfigureFn fn;
	};

	std::shared_mutex registryMutex;
	std::unordered_map<std::string, Logger*> loggers;
	std::vector<ConfigureFn> globalConfigurators;
	std::vector<PrefixConfigurator> prefixConfigurators;
};

}; // namespace Nibbler::Logging
