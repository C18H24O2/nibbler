/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DefaultFormatter.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 02:23:41 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/25 03:31:26 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Nibbler/Logging/IFormatter.hpp>

namespace Nibbler::Logging
{

class DefaultFormatter : public IFormatter
{
public:
	DEFAULT_CANONICAL_MEMBERS(DefaultFormatter)
	DefaultFormatter() noexcept = default;

	std::string format(const Logger& logger, const LogRecord& record) noexcept override;
};

}; // namespace Nibbler::Logging
