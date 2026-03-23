/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LogRecord.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 23:59:14 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/23 00:00:40 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
  
#include <chrono>
#include <source_location>
#include <string>
#include <thread>

#include <Nibbler/Logging/LogLevel.hpp>

namespace Nibbler::Logging
{
 
struct LogRecord
{
	LogLevel								level;
	std::string								message;
	std::source_location					location;
	std::chrono::system_clock::time_point	time;
	std::thread::id							threadId;
};

}; // namespace Nibbler::Logging
