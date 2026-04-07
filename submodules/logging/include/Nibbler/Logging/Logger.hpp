/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 20:50:08 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/07 02:29:43 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <atomic>
#include <filesystem>
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
#include <Nibbler/Logging/LoggerFactory.hpp>
#include <Nibbler/Util/NonCopyable.hpp>
#include <Nibbler/Util/NonMovable.hpp>

namespace Nibbler::Logging
{

class Logger final : private Util::NonCopyable {
public:
	explicit constexpr Logger(std::string_view name, std::source_location loc = std::source_location::current()) noexcept
		: name(name), loc(loc)
	{
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
	};

	constexpr ~Logger() noexcept
	{
		if (LoggerFactory::IsAlive())
			LoggerFactory::Instance().UnregisterLogger(*this);
	}

	constexpr void AddSink(std::shared_ptr<ISink> sink) noexcept
	{
		std::unique_lock lock(sinkMutex);
		sinks.push_back(std::move(sink));
	}

	constexpr void ClearSinks() noexcept
	{
		std::unique_lock lock(sinkMutex);
		sinks.clear();
	}

	constexpr void SetLevel(LogLevel logLevel) noexcept
	{
		minLogLevel.store(logLevel, std::memory_order_relaxed);
	}

	[[nodiscard]] constexpr LogLevel GetLevel() const noexcept
	{
		return minLogLevel.load(std::memory_order_relaxed);
	}

	[[nodiscard]] constexpr std::string_view GetName() const noexcept
	{
		return name;
	}

	[[nodiscard]] constexpr std::source_location GetLocation() const noexcept
	{
		return loc;
	}

	[[nodiscard]] constexpr std::string_view GetNibblerModule() const noexcept
	{
		return nibblerModule;
	}

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
	struct LogProxy
	{
		Logger& logger;
		const LogLevel& level;

		struct CallSite
		{
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

		[[nodiscard]] constexpr CallSite operator()(std::source_location loc = std::source_location::current()) noexcept
		{
			return { logger, level, loc };
		}
		[[nodiscard]] constexpr CallSite operator()(const LogMarker& marker, std::source_location loc = std::source_location::current()) noexcept
		{
			return { logger, level, loc, const_cast<LogMarker*>(&marker) };
		}
	};

public:
	LogProxy Spam  { *this, LogLevel::Spam  };
	LogProxy Trace { *this, LogLevel::Trace };
	LogProxy Debug { *this, LogLevel::Debug };
	LogProxy Info  { *this, LogLevel::Info  };
	LogProxy Warn  { *this, LogLevel::Warn  };
	LogProxy Error { *this, LogLevel::Error };
	LogProxy Fatal { *this, LogLevel::Fatal };

	constexpr void Flush() noexcept
	{
		std::shared_lock lock(sinkMutex);
		for (auto& sink : sinks)
			sink->Flush();
	}

private:
	std::string name;
	std::source_location loc;
	std::string nibblerModule;
	std::atomic<LogLevel> minLogLevel{LogLevel::Info};
	std::shared_mutex sinkMutex;
	std::vector<std::shared_ptr<ISink>> sinks;
};

}; // namespace Nibbler::Logging
