/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDLWindowProvider.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:59:04 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/28 12:59:14 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Nibbler/Plugins/SDL/SDLWindowProvider.hpp>

namespace Nibbler::Plugins::SDL
{

std::unique_ptr<Client::Window::Window> SDLWindowProvider::CreateWindow(const std::string& title, int width, int height)
{
	(void) title;
	(void) width;
	(void) height;

	return nullptr;
}

}; // namespace Nibbler::Plugins::SDL
