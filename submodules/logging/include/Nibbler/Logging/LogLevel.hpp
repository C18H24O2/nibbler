/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LogLevel.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 23:48:47 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/25 04:46:22 by kiroussa         ###   ########.fr       */
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
	LogLevel(uint16_t value, std::string_view name) noexcept;	
 
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
	LogLevel() noexcept;

	uint16_t priority;
	std::string_view name;
};
 
}; // namespace Nibbler::Logging
