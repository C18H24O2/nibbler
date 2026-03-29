/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientOptions.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 01:08:57 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/29 08:36:35 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <array>

#include <Nibbler/Launcher/Suboptions.hpp>

namespace Nibbler::Launcher
{

struct ClientOptions: public Suboptions
{
	std::string host;
	int port;
	std::string username;

	static constexpr std::string_view modeName = "client";
	static constexpr auto arguments = std::to_array<LaunchArgument<ClientOptions>>({
		{'H', "host", "Host to connect to", &ClientOptions::host},
		{'p', "port", "Port to connect to", &ClientOptions::port},
		{'u', "username", "Username to use", &ClientOptions::username}
	});

	int CallEntrypoint(Launcher::LaunchOptions& options) const noexcept;
};

}; // namespace Nibbler::Launcher
