/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IFormatter.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 00:39:11 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/25 03:31:08 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Nibbler/Util/Canonical.hpp>
#include <Nibbler/Logging/LogRecord.hpp>

namespace Nibbler::Logging
{

class Logger;

class IFormatter
{
public:
	DEFAULT_CANONICAL_MEMBERS(IFormatter)

	virtual std::string format(const Logger& logger, const LogRecord& record) noexcept = 0;
protected:
	IFormatter() noexcept = default;
};

}; // namespace Nibbler::Logging
