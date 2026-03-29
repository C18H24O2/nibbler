/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LaunchOptions.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 01:06:26 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/29 08:35:19 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <array>
#include <bit>
#include <charconv>
#include <cstring>
#include <getopt.h>
#include <optional>
#include <span>
#include <tuple>
#include <string_view>
#include <variant>
#include <print>

#include <Nibbler/Launcher/LaunchArgument.hpp>

namespace Nibbler::Launcher
{
struct LaunchOptions;
}; // namespace Nibbler::Launcher

#include <Nibbler/Launcher/Options/ClientOptions.hpp>
#include <Nibbler/Launcher/Options/ServerOptions.hpp>
#include <Nibbler/Launcher/Options/StandaloneOptions.hpp>

#include <Nibbler/Launcher/Suboptions.hpp>

namespace Nibbler::Launcher
{

template<typename T>
concept OptionsType = requires {
	{ T::modeName } -> std::convertible_to<std::string_view>;
	{ T::arguments } -> std::ranges::range;
	{ T::CallEntrypoint(std::declval<Launcher::LaunchOptions&>()) } -> std::same_as<int>;
};

using AllOptions = std::tuple<ClientOptions, ServerOptions, StandaloneOptions>;

template<typename Tuple, typename Func>
void ForEachOptionsType(Func&& f) {
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

struct LaunchOptions: public Suboptions
{
private:
	template <typename T, std::size_t N>
	struct GetoptBuilder
	{
		std::array<char, N * 3 + 3> shortOpts{};
		std::array<struct option, N + 1> longOpts{};

		constexpr GetoptBuilder(const std::array<LaunchArgument<T>, N>& args)
		{
			std::size_t si = 0;
			shortOpts[si++] = '+';
			shortOpts[si++] = ':';
			for (std::size_t i = 0; i < N; ++i)
			{
				shortOpts[si++] = args[i].shortName;
				using FieldPtr = typename LaunchArgument<T>::FieldPtr;
				bool needsArg = args[i].modifierFn ? args[i].requiresArg : !std::holds_alternative<bool T::*>(static_cast<FieldPtr>(args[i].fieldPtr));
				if (needsArg)
					shortOpts[si++] = ':';
				longOpts[i] = {
					args[i].longName.data(),
					needsArg ? required_argument : no_argument,
					nullptr,
					args[i].shortName
				};
			}
			shortOpts[si] = '\0';
			longOpts[N] = { nullptr, 0, nullptr, 0 };
		}
	};
public:
	constexpr LaunchOptions(OptionsVariant modeOptions) noexcept : modeOptions(modeOptions) {}
	OptionsVariant modeOptions;

	[[nodiscard]] static std::optional<LaunchOptions> Parse(int argc, char **argv) noexcept;

	template <typename T, std::size_t N>
	[[nodiscard]] static bool PartialParse(std::span<char*>& args, T& target, const std::array<LaunchArgument<T>, N>& arguments) noexcept
	{
		GetoptBuilder<T, N> builder(arguments);

		int argc = static_cast<int>(args.size());
		char** argv = args.data();
		optind = 1;

		int opt;
		int longIndex = -1;
		char* shortOpts = builder.shortOpts.data();
		auto longOpts = builder.longOpts.data();
		while ((opt = getopt_long(argc, argv, shortOpts, longOpts, &longIndex)) != -1)
		{
			if (opt == ':' || opt == '?')
			{
				if (opt == '?')
				{
					std::string_view optionStr;
					if (optopt)
						optionStr = std::string_view((char *) &optopt, 1);
					else
						optionStr = std::string_view(argv[optind - 1]).substr(2);
					std::println(stderr, "{}: invalid option -- '{}'", args[0], optionStr);
				}
				if (opt == ':')
					std::println(stderr, "{}: option requires an argument -- '{}'", args[0], (char)optopt);
				std::println(stderr, "Try '{} --help' for more information.", args[0]);
				return false;
			}

			for (auto& arg : arguments)
			{
				if (arg.shortName != opt)
					continue;

				if (arg.modifierFn)
					arg.modifierFn(&target);
				else
				{
					std::visit([&](auto fieldPtr) {
						using F = std::remove_reference_t<decltype(target.*fieldPtr)>;
						if constexpr (std::is_same_v<F, bool>)
							target.*fieldPtr = true;
						else
						{
							if (optarg == nullptr)
							{
								std::println(stderr, "Option {} requires an argument", arg.longName);
								return;
							}
							if constexpr (std::is_same_v<F, std::string>)
								target.*fieldPtr = optarg;
							else
							{
								F value{};
								auto [ptr, ec] = std::from_chars(optarg, optarg + std::strlen(optarg), value);
								if (ec == std::errc{})
									target.*fieldPtr = value;
							}
						}
					}, arg.fieldPtr);
				}
				break;
			}
		}

		args = args.subspan(optind - 1);
		args[0] = argv[0]; // keep the program name
		return true;
	}

	template<typename T, typename Base, typename Variant>
	static auto CastFieldPtr(const Variant& v)
	{
		return std::visit([](auto ptr) -> typename LaunchArgument<T>::FieldPtr
		{
			using Field = std::remove_reference_t<decltype(((Base*)nullptr)->*ptr)>;
			return static_cast<Field T::*>(ptr);
		}, v);
	}

	template<typename T>
	static std::optional<OptionsVariant> ParseMode(std::span<char*>& args) noexcept
	{
		constexpr std::size_t N = std::tuple_size_v<decltype(T::arguments)>;
		constexpr std::size_t M = std::tuple_size_v<decltype(builtinArguments)>;
		std::array<LaunchArgument<T>, N + M> arguments{};
		std::copy(T::arguments.begin(), T::arguments.end(), arguments.begin());
		size_t i = 0;
		for (auto&& arg : builtinArguments)
		{
			auto newPtr = CastFieldPtr<T, Suboptions>(arg.fieldPtr);
			auto newArg = LaunchArgument<T>{arg.shortName, arg.longName, arg.description, newPtr, arg.requiresArg, arg.modifierFn};
			arguments[N + i++] = newArg;
		}

		T target{};
		if (PartialParse(args, target, arguments))
			return target;
		return std::nullopt;
	}
};

}; // namespace Nibbler
