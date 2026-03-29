/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoggerFactory.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 17:54:58 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/28 17:55:21 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Nibbler/Logging/Logger.hpp>
#include <Nibbler/Logging/LoggerFactory.hpp>

namespace Nibbler::Logging
{

const Logger* LoggerFactory::Get(std::string_view name) noexcept
{
	std::shared_lock lock(registryMutex);
	for (auto& logger : loggers)
		if (logger->GetName() == name)
			return logger;
	return nullptr;
}

}; // namespace Nibbler::Logging
