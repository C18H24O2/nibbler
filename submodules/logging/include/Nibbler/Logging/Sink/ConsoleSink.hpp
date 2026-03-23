/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleSink.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 00:26:11 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/23 00:26:31 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Nibbler/Logging/ISink.hpp>

namespace Nibbler::Logging
{

class ConsoleSink : public ISink
{
public:
	virtual ~ConsoleSink() noexcept = default;
	ConsoleSink(const ConsoleSink&) = default;
	ConsoleSink(ConsoleSink&&) noexcept = default;
	ConsoleSink& operator=(const ConsoleSink&) = default;
	ConsoleSink& operator=(ConsoleSink&&) noexcept = default;

	void write(const LogRecord& record) noexcept override;
	void flush() noexcept override;
};

}; // namespace Nibbler::Logging
