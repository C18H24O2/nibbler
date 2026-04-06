/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDLWindow.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:12:18 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/06 13:48:45 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Nibbler/Plugins/SDL/SDLWindow.hpp>

namespace Nibbler::Plugins::SDL
{

SDLWindow::SDLWindow(SDLWindowPtr sdlWindow, std::string title, int width, int height) noexcept
	: Client::Window::Window(std::move(title), width, height), sdlWindow(std::move(sdlWindow))
{
}

void SDLWindow::Destroy() noexcept
{
}

}; // namespace Nibbler::Plugins::SDL
