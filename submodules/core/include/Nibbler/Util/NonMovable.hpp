/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NonMovable.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:02:16 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/08 22:02:19 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace Nibbler
{

class NonMovable
{
	protected:
		NonMovable() = default;
		~NonMovable() = default;

		NonMovable(NonMovable &&) = delete;
		NonMovable &operator=(NonMovable &&) = delete;
};

}; // namespace Nibbler
