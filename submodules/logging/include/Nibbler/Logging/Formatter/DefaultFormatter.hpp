/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DefaultFormatter.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 02:23:41 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/25 16:36:32 by kiroussa         ###   ########.fr       */
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

	[[nodiscard]] std::string Format(const Logger& logger, const LogRecord& record) noexcept override;
};

}; // namespace Nibbler::Logging
