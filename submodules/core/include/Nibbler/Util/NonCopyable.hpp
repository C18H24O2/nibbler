/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NonCopyable.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:02:06 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/08 23:57:39 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace Nibbler
{

class NonCopyable
{
	protected:
		NonCopyable() = default;
		~NonCopyable() = default;

		NonCopyable(const NonCopyable &) = delete;
		NonCopyable &operator=(const NonCopyable &) = delete;
};

}; // namespace Nibbler
