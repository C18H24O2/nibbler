/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleSink.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 00:26:37 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/25 16:37:09 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include <Nibbler/Logging/Sink/ConsoleSink.hpp>

namespace Nibbler::Logging
{

ConsoleSink::ConsoleSink(std::shared_ptr<IFormatter> formatter) noexcept
	: formatter(std::move(formatter)) {}

void ConsoleSink::Write(const Logger& logger, const LogRecord& record) noexcept
{
	std::cout << formatter->Format(logger, record) << std::endl;
}

void ConsoleSink::Flush() noexcept
{
	std::cout.flush();
}

}; // namespace Nibbler::Logging
