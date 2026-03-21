/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StandaloneOptions.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 01:08:47 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/21 20:59:03 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <array>
#include <Nibbler/Launcher/LaunchOptions.hpp>

namespace Nibbler::Launcher
{

struct StandaloneOptions
{
	static constexpr std::string_view modeName = "standalone";
	static constexpr std::array<LaunchArgument<StandaloneOptions>, 0> arguments{};
};

}; // namespace Nibbler
