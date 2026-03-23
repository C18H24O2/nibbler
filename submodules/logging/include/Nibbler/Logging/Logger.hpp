/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 20:50:08 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/23 00:28:47 by kiroussa         ###   ########.fr       */
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
	explicit Logger(std::source_location loc = std::source_location::current());

	virtual ~Logger() noexcept;

	void addSink(std::shared_ptr<ISink> sink);
	void clearSinks();

	void setLevel(LogLevel logLevel) noexcept;
	[[nodiscard]] LogLevel getLevel() const noexcept;

	[[nodiscard]] std::string_view name() const noexcept;
	[[nodiscard]] std::string_view file() const noexcept;

	template <typename... Args>
	void log(
		LogLevel logLevel,
		std::source_location loc,
		std::format_string<Args...> fmt,
		Args&&... args
	) noexcept {
		if (logLevel < minLogLevel.load(std::memory_order_relaxed))
			return;

		LogRecord record {
			.level = logLevel,
			.message = std::format(fmt, std::forward<Args>(args)...),
			.location = loc,
			.time = std::chrono::system_clock::now(),
			.threadId = std::this_thread::get_id(),
		};

		std::shared_lock lock(sinkMutex);
		for (auto& sink : sinks)
			sink->write(record);
	}

	void flush() noexcept;

private:
	void init(std::string_view name, std::string_view file);

	std::string module;
	std::string sourceFile;
	std::atomic<LogLevel> minLogLevel{LogLevel::Info};
	std::shared_mutex sinkMutex;
	std::vector<std::shared_ptr<ISink>> sinks;
};

}; // namespace Nibbler::Logging
