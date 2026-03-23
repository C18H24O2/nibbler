/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LogLevel.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 23:51:11 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/23 00:20:00 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits>
#include <Nibbler/Logging/LogLevel.hpp>

namespace Nibbler::Logging
{

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

const LogLevel LogLevel::All(0, "All");
const LogLevel LogLevel::Trace(100, "Trace");
const LogLevel LogLevel::Debug(200, "Debug");
const LogLevel LogLevel::Info(300, "Info");
const LogLevel LogLevel::Warn(400, "Warn");
const LogLevel LogLevel::Error(500, "Error");
const LogLevel LogLevel::Fatal(600, "Fatal");
const LogLevel LogLevel::Off(std::numeric_limits<uint16_t>::max(), "Off");

}; // namespace Nibbler::Logging
