/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 02:07:40 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/09 02:15:19 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <print>

#include <Nibbler/Launcher/LaunchOptions.hpp>

using namespace Nibbler::Launcher;

int main(int argc, char **argv)
{
	auto options = LaunchOptions::Parse(argc, argv);
	if (!options)
		return 1;

	std::println(stdout, "On launch le {} la", options->mode.GetName());
	return 0;
}
