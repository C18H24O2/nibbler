/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NonCopyable.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:02:06 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/23 00:13:29 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace Nibbler::Util
{

struct NonCopyable
{
	NonCopyable() = default;
	virtual ~NonCopyable() = default;

	NonCopyable(const NonCopyable &) = delete;
	NonCopyable &operator=(const NonCopyable &) = delete;
	NonCopyable(NonCopyable &&) = default;
	NonCopyable &operator=(NonCopyable &&) = default;
};

}; // namespace Nibbler:Util
