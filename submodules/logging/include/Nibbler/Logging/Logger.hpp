/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 20:50:08 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/25 16:34:23 by kiroussa         ###   ########.fr       */
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

	void AddSink(std::shared_ptr<ISink> sink);
	void ClearSinks();

	void SetLevel(LogLevel logLevel) noexcept;
	[[nodiscard]] LogLevel GetLevel() const noexcept;

	[[nodiscard]] std::string_view GetName() const noexcept;
	[[nodiscard]] std::source_location GetLocation() const noexcept;
	[[nodiscard]] std::string_view GetNibblerModule() const noexcept;

	template <typename... Args>
	void Log(LogLevel logLevel, std::source_location loc, std::format_string<Args...> fmt, Args&&... args) noexcept
	{
		Log(nullptr, logLevel, loc, fmt, std::forward<Args>(args)...);
	}

	template <typename... Args>
	void Log(
		LogMarker* marker,
		LogLevel logLevel,
		std::source_location loc,
		std::format_string<Args...> fmt,
		Args&&... args
	) noexcept {
		if (logLevel.GetPriority() < minLogLevel.load(std::memory_order_relaxed).GetPriority())
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
			sink->Write(*this, record);
	}

private:
	struct LogProxy {
		Logger& logger;
		const LogLevel& level;

		struct CallSite {
			Logger& logger;
			const LogLevel& level;
			std::source_location loc;
			LogMarker* marker = nullptr;

			template <typename... Args>
			void Emit(std::format_string<Args...> fmt, Args&&... args) noexcept
			{
				logger.Log(marker, level, loc, fmt, std::forward<Args>(args)...);
			}
		};

		CallSite operator()(std::source_location loc = std::source_location::current()) noexcept;
		CallSite operator()(const LogMarker& marker, std::source_location loc = std::source_location::current()) noexcept;
	};

public:
	LogProxy Trace { *this, LogLevel::Trace };
	LogProxy Debug { *this, LogLevel::Debug };
	LogProxy Info  { *this, LogLevel::Info  };
	LogProxy Warn  { *this, LogLevel::Warn  };
	LogProxy Error { *this, LogLevel::Error };
	LogProxy Fatal { *this, LogLevel::Fatal };

	void Flush() noexcept;

private:
	std::string name;
	std::source_location loc;
	std::string nibblerModule;
	std::atomic<LogLevel> minLogLevel{LogLevel::Info};
	std::shared_mutex sinkMutex;
	std::vector<std::shared_ptr<ISink>> sinks;
};

}; // namespace Nibbler::Logging
