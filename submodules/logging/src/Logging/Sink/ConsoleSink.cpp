/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleSink.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 00:26:37 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/23 00:26:40 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Nibbler/Logging/Sink/ConsoleSink.hpp>

namespace Nibbler::Logging
{

void ConsoleSink::write(const LogRecord& record) noexcept
{
	std::cout << record.message << std::endl;
}

void ConsoleSink::flush() noexcept
{
	std::cout.flush();
}

}; // namespace Nibbler::Logging
