/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Concat.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:28:55 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/28 13:33:33 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <array>
#include <string_view>

namespace Nibbler::Util
{

template<std::string_view const&... Svs>
struct concat {
private:
	static constexpr auto impl()
	{
		constexpr std::size_t len = (Svs.size() + ...);
		std::array<char, len + 1> arr{};
		std::size_t i = 0;
		((std::copy(Svs.begin(), Svs.end(), arr.begin() + i), i += Svs.size()), ...);
		arr[len] = '\0';
		return arr;
	}

	static constexpr auto arr = impl();
public:
	static constexpr std::string_view value{arr.data(), arr.size() - 1};
};

template<std::string_view const&... Svs>
static constexpr auto concat_v = concat<Svs...>::value;

}; // namespace Nibbler::Util
