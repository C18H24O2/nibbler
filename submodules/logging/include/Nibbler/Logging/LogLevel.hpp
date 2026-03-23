/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LogLevel.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 23:48:47 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/23 00:19:43 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
 
#include <cstdint>
#include <string_view>

namespace Nibbler::Logging
{
 
class LogLevel final {
public:
	constexpr LogLevel(uint16_t value, std::string_view name) noexcept
		: priority(value), name(name) {}
	~LogLevel() noexcept = default;
	LogLevel(const LogLevel&) noexcept = default;
	LogLevel(LogLevel&&) noexcept = default;
	LogLevel& operator=(const LogLevel&) noexcept = default;
	LogLevel& operator=(LogLevel&&) noexcept = default;
 
	explicit operator bool() const = delete;
 
	[[nodiscard]] std::string_view getName() const noexcept;
	[[nodiscard]] uint16_t getPriority() const noexcept;
 
	[[nodiscard]] bool operator==(const LogLevel&) const noexcept;
	[[nodiscard]] std::strong_ordering operator<=>(const LogLevel& other) const noexcept;
 
	static const LogLevel All;
	static const LogLevel Trace;
	static const LogLevel Debug;
	static const LogLevel Info;
	static const LogLevel Warn;
	static const LogLevel Error;
	static const LogLevel Fatal;
	static const LogLevel Off;
 
private:
	constexpr LogLevel() noexcept
		: priority(0), name("Off") {}

	uint16_t priority;
	std::string_view name;
};
 
#ifndef LOG_MIN_LEVEL
	#define LOG_MIN_LEVEL LogLevel::Info
#endif

}; // namespace Nibbler::Logging
