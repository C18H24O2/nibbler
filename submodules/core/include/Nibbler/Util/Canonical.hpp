/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Canonical.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 00:39:43 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/05 23:44:04 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace Nibbler::Util
{

#define DEFAULT_CANONICAL_MEMBERS(ClassName)			\
	constexpr virtual ~ClassName() noexcept = default;			\
	constexpr ClassName(const ClassName&) noexcept = default;				\
	constexpr ClassName(ClassName&&) noexcept = default;			\
	constexpr ClassName& operator=(const ClassName&) noexcept = default;	\
	constexpr ClassName& operator=(ClassName&&) noexcept = default;

#define DEFAULT_CANONICAL_FINAL_MEMBERS(ClassName)		\
	constexpr ~ClassName() noexcept = default;					\
	constexpr ClassName(const ClassName&) noexcept = default;				\
	constexpr ClassName(ClassName&&) noexcept = default;			\
	constexpr ClassName& operator=(const ClassName&) noexcept = default;	\
	constexpr ClassName& operator=(ClassName&&) noexcept = default;

#define DEFAULT_CANONICAL_NODTOR(ClassName)			\
	constexpr ClassName(const ClassName&) noexcept = default;				\
	constexpr ClassName(ClassName&&) noexcept = default;			\
	constexpr ClassName& operator=(const ClassName&) noexcept = default;	\
	constexpr ClassName& operator=(ClassName&&) noexcept = default;

}; // namespace Nibbler::Util
