/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerOptions.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 01:09:34 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/10 11:33:34 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Nibbler/Launcher/LaunchOptions.hpp>

namespace Nibbler::Launcher
{

struct ServerOptions
{
	std::string host;
	int port;
	
	static constexpr LaunchMode mode = LaunchMode::SERVER;
	static constexpr std::array<LaunchArgument, 2> arguments{
		LaunchArgument{'H', "host", "Address to listen on"},
		LaunchArgument{'p', "port", "Port to listen on"}
	};
};

}; // namespace Nibbler
