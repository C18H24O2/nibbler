/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerOptions.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 01:09:34 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/25 04:24:14 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <array>
#include <Nibbler/Launcher/LaunchOptions.hpp>

namespace Nibbler::Launcher
{

struct ServerOptions
{
	std::string host;
	int port;
	
	static constexpr std::string_view modeName = "server";
	static constexpr auto arguments = std::to_array<LaunchArgument<ServerOptions>>({
		{'H', "host", "Address to listen on", &ServerOptions::host},
		{'p', "port", "Port to listen on", &ServerOptions::port}
	});

	void CallEntrypoint(Launcher::LaunchOptions& options) const noexcept;
};

}; // namespace Nibbler
