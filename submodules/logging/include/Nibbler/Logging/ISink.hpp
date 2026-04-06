/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ISink.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 23:45:09 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/05 18:53:05 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Nibbler/Util/Canonical.hpp>
#include <Nibbler/Logging/LogRecord.hpp>

namespace Nibbler::Logging
{

class Logger;

class ISink
{
public:
	DEFAULT_CANONICAL_MEMBERS(ISink)

	virtual void Write(const Logger& logger, const LogRecord& record) noexcept = 0;
	virtual void Flush() noexcept = 0;
protected:
	ISink() noexcept = default;
};

}; // namespace Nibbler::Logging
