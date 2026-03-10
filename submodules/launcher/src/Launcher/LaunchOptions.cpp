/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LaunchOptions.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 01:13:04 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/10 11:34:22 by kiroussa         ###   ########.fr       */
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
	forEachOptionsType<AllOptions>([&optionNames]<typename T>() {
		if (!optionNames.empty())
			optionNames += "|";
		optionNames += T::mode.GetName();
	});
	std::println(stream, "Usage: nibbler [{}] [options...]", optionNames);

	if (help)
	{
		size_t maxNameSize = 0;
		forEachOptionsType<AllOptions>([&maxNameSize]<typename T>() {
			for (auto&& arg : T::arguments)
				maxNameSize = std::max(maxNameSize, arg.longName.size());
		});

		forEachOptionsType<AllOptions>([stream, maxNameSize]<typename T>() {
			if (T::arguments.empty())
				return;
			std::println(stream, "{}", T::mode.GetName());
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
		return LaunchOptions{LaunchMode::STANDALONE, 0, StandaloneOptions{}};
	else
	{
		std::string type = argv[1];
		LaunchMode mode = LaunchMode::STANDALONE;
		if (type.size() == 0 || type[0] != '-')
		{
			auto modeOpt = LaunchMode::FromString(type);
			if (!modeOpt)
			{
				printUsage(false);
				return std::nullopt;
			}
			mode = *modeOpt;
			argc--;
			argv++;
		}

		return mode.DelegateParse(argc, argv);
	}
	return std::nullopt;
}

}; // namespace Nibbler
