/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleSink.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 00:26:11 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/25 16:36:19 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Nibbler/Util/Canonical.hpp>
#include <Nibbler/Logging/IFormatter.hpp>
#include <Nibbler/Logging/ISink.hpp>

namespace Nibbler::Logging
{

class ConsoleSink : public ISink
{
public:
	DEFAULT_CANONICAL_MEMBERS(ConsoleSink)
	ConsoleSink(std::shared_ptr<IFormatter> formatter) noexcept;

	void Write(const Logger& logger, const LogRecord& record) noexcept override;
	void Flush() noexcept override;
private:
	ConsoleSink() noexcept = delete;
	std::shared_ptr<IFormatter> formatter;
};

}; // namespace Nibbler::Logging
