/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StandaloneOptions.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 01:08:47 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/27 23:53:01 by kiroussa         ###   ########.fr       */
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

	void CallEntrypoint(Launcher::LaunchOptions& options) const noexcept;
};

}; // namespace Nibbler::Launcher
