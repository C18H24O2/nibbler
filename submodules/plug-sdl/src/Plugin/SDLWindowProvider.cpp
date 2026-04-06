/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDLWindowProvider.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:59:04 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/06 14:07:39 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Nibbler/Plugins/SDL/SDLWindowProvider.hpp>
#include <Nibbler/Plugins/SDL/SDLWindow.hpp>

namespace Nibbler::Plugins::SDL
{

std::unique_ptr<Client::Window::Window> SDLWindowProvider::CreateWindow(
	const std::string& title,
	int width,
	int height
) {
	if (width <= 0 || height <= 0 || title.empty())
		return nullptr;

	//TODO: get flags from the game's main loop's GpuContext's GraphicsApi
	SDL_Window* window = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN);
	if (!window)
		return nullptr;
	return std::make_unique<SDLWindow>(SDLWindowPtr(window), title, width, height);
}

}; // namespace Nibbler::Plugins::SDL
