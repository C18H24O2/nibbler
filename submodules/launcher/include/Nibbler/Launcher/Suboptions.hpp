/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Suboptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 23:48:58 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/28 00:44:36 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <array>
#include <Nibbler/Launcher/LaunchArgument.hpp>

namespace Nibbler::Launcher
{

struct Suboptions
{
	bool help = false;
	int verbosity = 0;

	virtual ~Suboptions() = default;
};

inline constexpr auto builtinArguments = std::to_array<LaunchArgument<Suboptions>>({
	{'d', "verbose", "Increase verbosity", &Suboptions::verbosity, false, [](void *opt){ static_cast<Suboptions*>(opt)->verbosity++; }},
	{'h', "help", "Display this help message", &Suboptions::help},
});

}; // namespace Nibbler::Launcher
