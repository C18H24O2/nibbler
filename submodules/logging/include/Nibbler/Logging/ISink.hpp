/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ISink.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 23:45:09 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/23 00:01:30 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Nibbler/Logging/LogRecord.hpp>

namespace Nibbler::Logging
{

class ISink
{
public:
	virtual ~ISink() noexcept = default;
	ISink(const ISink&) noexcept = default;
	ISink(ISink&&) noexcept = default;
	ISink& operator=(const ISink&) noexcept = default;
	ISink& operator=(ISink&&) noexcept = default;

	virtual void write(const LogRecord& record) noexcept = 0;
	virtual void flush() noexcept = 0;
};

}; // namespace Nibbler::Logging
