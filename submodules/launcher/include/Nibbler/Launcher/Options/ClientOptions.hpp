/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientOptions.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 01:08:57 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/09 03:13:18 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Nibbler/Launcher/LaunchArgument.hpp>

namespace Nibbler::Launcher
{

struct ClientOptions
{
	std::string host;
	int port;
	std::string username;

	static constexpr std::string_view name = "client";
	static constexpr std::array<LaunchArgument, 3> arguments{
		LaunchArgument{'H', "host", "Host to connect to"},
		LaunchArgument{'p', "port", "Port to connect to"},
		LaunchArgument{'u', "username", "Username to use"}
	};
};

}; // namespace Nibbler
