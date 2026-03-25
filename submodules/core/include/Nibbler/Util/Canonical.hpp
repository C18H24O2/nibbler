/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Canonical.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 00:39:43 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/25 03:50:57 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace Nibbler::Util
{

#define DEFAULT_CANONICAL_MEMBERS(ClassName)			\
	virtual ~ClassName() noexcept = default;			\
	ClassName(const ClassName&) = default;				\
	ClassName(ClassName&&) noexcept = default;			\
	ClassName& operator=(const ClassName&) = default;	\
	ClassName& operator=(ClassName&&) noexcept = default;

#define DEFAULT_CANONICAL_FINAL_MEMBERS(ClassName)		\
	~ClassName() noexcept = default;					\
	ClassName(const ClassName&) = default;				\
	ClassName(ClassName&&) noexcept = default;			\
	ClassName& operator=(const ClassName&) = default;	\
	ClassName& operator=(ClassName&&) noexcept = default;

}; // namespace Nibbler::Util
