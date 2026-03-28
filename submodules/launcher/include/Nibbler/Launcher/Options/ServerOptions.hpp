/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerOptions.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 01:09:34 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/27 23:53:36 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <array>

#include <Nibbler/Launcher/Suboptions.hpp>

namespace Nibbler::Launcher
{

struct ServerOptions: public Suboptions
{
	std::string host = "0.0.0.0";
	int port = 4242;
	int width = 15;
	int height = 15;
	
	static constexpr std::string_view modeName = "server";
	static constexpr auto arguments = std::to_array<LaunchArgument<ServerOptions>>({
		{'L', "host", "Address to listen on (default: 0.0.0.0)", &ServerOptions::host},
		{'p', "port", "Port to listen on (default: 4242)", &ServerOptions::port},
		{'W', "width", "The width of the arena (default: 15)", &ServerOptions::width},
		{'H', "height", "The height of the arena (default: 15)", &ServerOptions::height}
	});

	void CallEntrypoint(Launcher::LaunchOptions& options) const noexcept;
};

}; // namespace Nibbler::Launcher
