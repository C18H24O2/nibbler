/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 20:50:08 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/25 03:42:56 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <atomic>
#include <format>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <source_location>
#include <string>
#include <string_view>
#include <vector>

#include <Nibbler/Logging/ISink.hpp>
#include <Nibbler/Logging/LogLevel.hpp>
#include <Nibbler/Logging/LogRecord.hpp>
#include <Nibbler/Util/NonCopyable.hpp>
#include <Nibbler/Util/NonMovable.hpp>

namespace Nibbler::Logging
{

class Logger final : private Util::NonCopyable, private Util::NonMovable {
public:
	explicit Logger(std::string_view name, std::source_location loc = std::source_location::current());
	virtual ~Logger() noexcept;

	void addSink(std::shared_ptr<ISink> sink);
	void clearSinks();

	void setLevel(LogLevel logLevel) noexcept;
	[[nodiscard]] LogLevel getLevel() const noexcept;

	[[nodiscard]] std::string_view getName() const noexcept;
	[[nodiscard]] std::source_location getLocation() const noexcept;
	[[nodiscard]] std::string_view getNibblerModule() const noexcept;

	template <typename... Args>
	void log(LogLevel logLevel, std::source_location loc, std::format_string<Args...> fmt, Args&&... args) noexcept
	{
		log(nullptr, logLevel, loc, fmt, std::forward<Args>(args)...);
	}

	template <typename... Args>
	void log(
		LogMarker* marker,
		LogLevel logLevel,
		std::source_location loc,
		std::format_string<Args...> fmt,
		Args&&... args
	) noexcept {
		if (logLevel < minLogLevel.load(std::memory_order_relaxed))
			return;

		LogRecord record {
			.level = logLevel,
			.marker = marker,
			.message = std::format(fmt, std::forward<Args>(args)...),
			.location = loc,
			.time = std::chrono::system_clock::now(),
			.threadId = std::this_thread::get_id(),
		};

		std::shared_lock lock(sinkMutex);
		for (auto& sink : sinks)
			sink->write(*this, record);
	}

private:
	struct LogProxy {
		Logger& logger;
		LogLevel level;

		template <typename... Args>
		struct Caller {
			Caller(Logger& logger, LogLevel level, std::source_location loc,
				   std::format_string<Args...> fmt, Args&&... args) noexcept
			{ logger.log(level, loc, fmt, std::forward<Args>(args)...); }
		};

		struct CallSite {
			Logger& logger;
			LogLevel level;
			std::source_location loc;
			LogMarker* marker = nullptr;

			template <typename... Args>
			void emit(std::format_string<Args...> fmt, Args&&... args) noexcept
			{ logger.log(marker, level, loc, fmt, std::forward<Args>(args)...); }
		};

		CallSite operator()(std::source_location loc = std::source_location::current()) noexcept;
		CallSite operator()(const LogMarker& marker, std::source_location loc = std::source_location::current()) noexcept;
	};

public:
	LogProxy trace { *this, LogLevel::Trace };
	LogProxy debug { *this, LogLevel::Debug };
	LogProxy info  { *this, LogLevel::Info  };
	LogProxy warn  { *this, LogLevel::Warn  };
	LogProxy error { *this, LogLevel::Error };
	LogProxy fatal { *this, LogLevel::Fatal };

	void flush() noexcept;

private:
	std::string name;
	std::source_location loc;
	std::string nibblerModule;
	std::atomic<LogLevel> minLogLevel{LogLevel::Info};
	std::shared_mutex sinkMutex;
	std::vector<std::shared_ptr<ISink>> sinks;
};

}; // namespace Nibbler::Logging
