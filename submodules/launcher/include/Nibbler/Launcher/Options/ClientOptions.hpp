/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientOptions.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 01:08:57 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/10 11:33:34 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Nibbler/Launcher/LaunchOptions.hpp>

namespace Nibbler::Launcher
{

struct ClientOptions
{
	std::string host;
	int port;
	std::string username;

	static constexpr LaunchMode mode = LaunchMode::CLIENT;
	static constexpr std::array<LaunchArgument, 3> arguments{
		LaunchArgument{'H', "host", "Host to connect to"},
		LaunchArgument{'p', "port", "Port to connect to"},
		LaunchArgument{'u', "username", "Username to use"}
	};
};

}; // namespace Nibbler
