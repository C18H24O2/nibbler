/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LogLevel.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 23:51:11 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/25 04:43:49 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits>
#include <Nibbler/Logging/LogLevel.hpp>

namespace Nibbler::Logging
{

LogLevel::LogLevel(uint16_t value, std::string_view name) noexcept
	: priority(value), name(name) {}

LogLevel::LogLevel() noexcept
	: priority(0), name("Off") {}

std::string_view LogLevel::getName() const noexcept
{
	return name;
}

uint16_t LogLevel::getPriority() const noexcept
{
	return priority;
}

bool LogLevel::operator==(const LogLevel& other) const noexcept
{
	return priority == other.priority;
}

std::strong_ordering LogLevel::operator<=>(const LogLevel& other) const noexcept
{
	return priority <=> other.priority;
}

const LogLevel LogLevel::All(0, "ALL");
const LogLevel LogLevel::Trace(100, "TRACE");
const LogLevel LogLevel::Debug(200, "DEBUG");
const LogLevel LogLevel::Info(300, "INFO");
const LogLevel LogLevel::Warn(400, "WARN");
const LogLevel LogLevel::Error(500, "ERROR");
const LogLevel LogLevel::Fatal(600, "FATAL");
const LogLevel LogLevel::Off(std::numeric_limits<uint16_t>::max(), "OFF");

}; // namespace Nibbler::Logging
