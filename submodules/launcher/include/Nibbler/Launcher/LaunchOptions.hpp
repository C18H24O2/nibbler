/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LaunchOptions.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 01:06:26 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/10 11:35:02 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <optional>
#include <variant>

#include <Nibbler/Launcher/LaunchArgument.hpp>

namespace Nibbler::Launcher
{

struct LaunchOptions;

};

#include <Nibbler/Launcher/LaunchMode.hpp>

#include <Nibbler/Launcher/Options/ClientOptions.hpp>
#include <Nibbler/Launcher/Options/ServerOptions.hpp>
#include <Nibbler/Launcher/Options/StandaloneOptions.hpp>

namespace Nibbler::Launcher
{

template<typename T>
concept OptionsType = requires {
	{ T::mode } -> std::convertible_to<LaunchMode>;
    { T::arguments } -> std::ranges::range;
};

using AllOptions = std::tuple<ClientOptions, ServerOptions, StandaloneOptions>;

template<typename Tuple, typename Func>
void forEachOptionsType(Func&& f) {
    [&]<std::size_t... Is>(std::index_sequence<Is...>) {
        (f.template operator()<std::tuple_element_t<Is, Tuple>>(), ...);
    }(std::make_index_sequence<std::tuple_size_v<Tuple>>{});
}

template<typename Tuple>
struct TupleToVariant;

template<typename... Ts>
struct TupleToVariant<std::tuple<Ts...>> {
    using type = std::variant<Ts...>;
};

using OptionsVariant = typename TupleToVariant<AllOptions>::type;

struct LaunchOptions
{
	LaunchMode mode;
	int verbosity;
	OptionsVariant options;

	[[nodiscard]] static std::optional<LaunchOptions> Parse(int argc, char **argv) noexcept;
};

}; // namespace Nibbler
