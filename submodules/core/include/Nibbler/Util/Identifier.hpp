/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Identifier.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:27:08 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/25 16:29:43 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <string_view>

#include <Nibbler/Util/Canonical.hpp>

namespace Nibbler::Util
{

class Identifier
{
	public:
		DEFAULT_CANONICAL_MEMBERS(Identifier)
		Identifier(std::string_view domain, std::string_view path) noexcept;
		Identifier(std::string_view path) noexcept;

		[[nodiscard]] std::string_view GetDomain() const noexcept;
		[[nodiscard]] std::string_view GetPath() const noexcept;

		[[nodiscard]] std::string toString() const noexcept;

		static constexpr std::string_view defaultDomain = "nibbler";

	private:
		Identifier() noexcept = delete;
};

} // namespace Nibbler::Util
