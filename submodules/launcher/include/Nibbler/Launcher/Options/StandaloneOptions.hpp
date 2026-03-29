/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StandaloneOptions.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 01:08:47 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/29 08:36:46 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <array>

#include <Nibbler/Launcher/Suboptions.hpp>

namespace Nibbler::Launcher
{

struct StandaloneOptions: public Suboptions
{
	int width = 15;
	int height = 15;

	static constexpr std::string_view modeName = "standalone";
	static constexpr auto arguments = std::to_array<LaunchArgument<StandaloneOptions>>({
		{'W', "width", "The width of the arena (default: 15)", &StandaloneOptions::width},
		{'H', "height", "The height of the arena (default: 15)", &StandaloneOptions::height}
	});

	int CallEntrypoint(Launcher::LaunchOptions& options) const noexcept;
};

}; // namespace Nibbler::Launcher
