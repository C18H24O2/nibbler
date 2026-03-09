/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StandaloneOptions.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 01:08:47 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/09 03:13:38 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Nibbler/Launcher/LaunchArgument.hpp>

namespace Nibbler::Launcher
{

struct StandaloneOptions
{
	static constexpr std::string_view name = "standalone";
	static constexpr std::array<LaunchArgument, 0> arguments{};
};

}; // namespace Nibbler
