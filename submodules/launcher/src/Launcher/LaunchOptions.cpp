/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LaunchOptions.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 01:13:04 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/25 04:03:23 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <cstdio>
#include <print>
#include <span>

#include <Nibbler/Launcher/LaunchOptions.hpp>

namespace Nibbler::Launcher
{

constexpr void printUsage(bool help)
{
	std::FILE *const stream = help ? stdout : stderr;

	std::string optionNames;
	ForEachOptionsType<AllOptions>([&optionNames]<typename T>() {
		if (!optionNames.empty())
			optionNames += "|";
		optionNames += T::modeName;
	});
	std::println(stream, "Usage: nibbler [{}] [options...]", optionNames);

	if (help)
	{
		size_t maxNameSize = 0;
		ForEachOptionsType<AllOptions>([&maxNameSize]<typename T>() {
			for (auto&& arg : T::arguments)
				maxNameSize = std::max(maxNameSize, arg.longName.size());
		});

		ForEachOptionsType<AllOptions>([stream, maxNameSize]<typename T>() {
			if (T::arguments.empty())
				return;
			std::string name(T::modeName);
			name[0] = std::toupper(name[0]);
			std::println(stream, "{}-specific Options:", name);
			for (auto&& arg : T::arguments)
			{
				size_t curSize = arg.longName.size();
				std::string spacing(maxNameSize - curSize, ' ');
				std::print(stream, "  -{}, --{}{}", arg.shortName, arg.longName, spacing);
				if (!arg.description.empty())
					std::println(stream, " {}", arg.description);
			}
			std::println(stream);
		});
		std::println(stream, "Options:");
		for (auto&& arg : builtinArguments)
		{
			std::string spacing(maxNameSize - arg.longName.size(), ' ');
			std::print(stream, "  -{}, --{}{}", arg.shortName, arg.longName, spacing);
			if (!arg.description.empty())
				std::println(stream, " {}", arg.description);
		}
	}
}

std::optional<LaunchOptions> LaunchOptions::Parse(int argc, char **argv) noexcept
{
	std::span<char*> args(argv, argc);

	LaunchOptions options{false, 0, StandaloneOptions{}};
	if (!PartialParse(args, options, builtinArguments))
		return std::nullopt;
	if (options.help)
	{
		printUsage(true);
		return options;
	}

	if (args.size() <= 1)
		return options;

	std::string_view mode = args[1];
	args = args.subspan(1);
	args[0] = argv[0]; // keep the program name

	std::optional<std::string_view> modeName = std::nullopt;
	ForEachOptionsType<AllOptions>([&modeName, mode]<typename T>() {
		if (mode == T::modeName)
			modeName = T::modeName;
	});
	if (!modeName)
	{
		std::println(stderr, "{}: unknown mode -- \"{}\"", args[0], mode);
		printUsage(false);
		return std::nullopt;
	}

	std::optional<OptionsVariant> modeOptions = std::nullopt;
	ForEachOptionsType<AllOptions>([&modeOptions, mode, &args]<typename T>() {
		if (mode == T::modeName)
			modeOptions = LaunchOptions::ParseMode<T>(args);
	});
	if (!modeOptions)
		return std::nullopt;

	options.modeOptions = *modeOptions;
	return options;
}

}; // namespace Nibbler
