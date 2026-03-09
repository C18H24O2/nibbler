/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NonMovable.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:02:16 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/09 00:30:14 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace Nibbler
{

class NonMovable
{
	protected:
		NonMovable() = default;
		virtual ~NonMovable() = default;
	public:
		NonMovable(const NonMovable&) = default;
		NonMovable(NonMovable&&) noexcept = delete;
		NonMovable& operator=(const NonMovable&) = default;
		NonMovable& operator=(NonMovable&&) noexcept = delete;
};

}; // namespace Nibbler
