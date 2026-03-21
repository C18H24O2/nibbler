/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LaunchOptions.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 01:13:04 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/21 21:02:52 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <getopt.h>
#include <cstdio>
#include <print>

#include <Nibbler/Launcher/LaunchOptions.hpp>

namespace Nibbler::Launcher
{

static inline void printUsage(bool help)
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
			std::println(stream, "{}", T::modeName);
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
		std::println(stream, "  -d, --verbose   Increase verbosity");
		std::println(stream, "  -h, --help      Display this help message");
	}
}

std::optional<LaunchOptions> LaunchOptions::Parse(int argc, char **argv) noexcept
{
	if (argc == 1)
		return LaunchOptions{0, StandaloneOptions{}};
	else
	{
		// Run the parser first for -d/-h


		std::string type = argv[1];
		std::string_view modeName = StandaloneOptions::modeName;
		if (type.size() == 0 || type[0] != '-')
		{
			std::optional<std::string_view> modeOpt = std::nullopt;
			ForEachOptionsType<AllOptions>([&modeOpt, type]<typename T>() {
				if (type == T::modeName)
					modeOpt = type;
			});
			if (!modeOpt)
			{
				printUsage(false);
				return std::nullopt;
			}
			modeName = *modeOpt;
			argc--;
			argv++;
		}

		std::optional<OptionsVariant> modeOptions = std::nullopt;
		ForEachOptionsType<AllOptions>([&modeOptions, modeName, argc, argv]<typename T>() {
			if (modeName == T::modeName)
				modeOptions = LaunchOptions::ParseMode<T>(argc, argv);
		});

		if (!modeOptions)
		{
			printUsage(false);
			return std::nullopt;
		}

		return LaunchOptions{0, *modeOptions};
	}
	return std::nullopt;
}

}; // namespace Nibbler
