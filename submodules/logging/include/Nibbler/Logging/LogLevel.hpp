/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LogLevel.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 23:48:47 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/07 03:19:43 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
 
#include <cstdint>
#include <string_view>

#include <Nibbler/Util/Canonical.hpp>

namespace Nibbler::Logging
{
 
class LogLevel final {
public:
	DEFAULT_CANONICAL_FINAL_MEMBERS(LogLevel)
	constexpr LogLevel(uint16_t value, std::string_view name) noexcept
		: priority(value), name(name) {}
 
	explicit operator bool() const = delete;
 
	[[nodiscard]] constexpr std::string_view GetName() const noexcept
	{
		return name;
	}

	[[nodiscard]] constexpr uint16_t GetPriority() const noexcept
	{
		return priority;
	}
 
	[[nodiscard]] constexpr bool operator==(const LogLevel& other) const noexcept
	{
		return priority == other.priority;
	}

	[[nodiscard]] constexpr std::strong_ordering operator<=>(const LogLevel& other) const noexcept
	{
		return priority <=> other.priority;
	}
 
	static const LogLevel All;
	static const LogLevel Spam;
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

inline constexpr LogLevel LogLevel::All{0, "ALL"};
inline constexpr LogLevel LogLevel::Spam{50, "SPAM"};
inline constexpr LogLevel LogLevel::Trace{100, "TRACE"};
inline constexpr LogLevel LogLevel::Debug{200, "DEBUG"};
inline constexpr LogLevel LogLevel::Info{300, "INFO"};
inline constexpr LogLevel LogLevel::Warn{400, "WARN"};
inline constexpr LogLevel LogLevel::Error{500, "ERROR"};
inline constexpr LogLevel LogLevel::Fatal{600, "FATAL"};
inline constexpr LogLevel LogLevel::Off{std::numeric_limits<uint16_t>::max(), "OFF"};
 
}; // namespace Nibbler::Logging
