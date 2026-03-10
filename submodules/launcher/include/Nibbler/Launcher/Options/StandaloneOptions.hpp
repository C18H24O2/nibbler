/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StandaloneOptions.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 01:08:47 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/10 11:33:22 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Nibbler/Launcher/LaunchOptions.hpp>

namespace Nibbler::Launcher
{

struct StandaloneOptions
{
	static constexpr LaunchMode mode = LaunchMode::STANDALONE;
	static constexpr std::array<LaunchArgument, 0> arguments{};
};

}; // namespace Nibbler
