/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerOptions.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 01:09:34 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/09 03:13:28 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Nibbler/Launcher/LaunchArgument.hpp>

namespace Nibbler::Launcher
{

struct ServerOptions
{
	std::string host;
	int port;
	
	static constexpr std::string_view name = "server";
	static constexpr std::array<LaunchArgument, 2> arguments{
		LaunchArgument{'H', "host", "Address to listen on"},
		LaunchArgument{'p', "port", "Port to listen on"}
	};
};

}; // namespace Nibbler
