/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Typename.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:18:16 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/28 14:39:39 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string_view>

namespace Nibbler::Util
{

template<typename T>
[[nodiscard]] consteval std::string_view Typename()
{
	std::string_view name;
#if defined(__clang__) || defined(__GNUC__)
	name = __PRETTY_FUNCTION__;
	// clang           "std::string_view type_name() [T = MyCoolType]"
	// gcc:  "consteval std::string_view type_name() [with T = MyCoolType]"
	auto start = name.rfind("T = ") + 4;
	auto end = name.rfind(']');
#elif defined(_MSC_VER)
	name = __FUNCSIG__;
	// msvc: "class std::basic_string_view<...> __cdecl type_name<class MyCoolType>(void)"
	auto start = name.rfind("type_name<") + 10;
	auto end = name.rfind(">(void)");
#endif
	return name.substr(start, end - start);
}

}; // namespace Nibbler::Util
