/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDLWindow.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 11:45:00 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/06 13:48:27 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>

#include <SDL3/SDL.h>

#include <Nibbler/Client/Window/Window.hpp>

namespace Nibbler::Plugins::SDL
{

struct SDLWindowDeleter
{
	void operator()(SDL_Window* window) const noexcept
	{
		SDL_DestroyWindow(window);
	}
};

using SDLWindowPtr = std::unique_ptr<SDL_Window, SDLWindowDeleter>;

class SDLWindow final: public Client::Window::Window
{
public:
	SDLWindow(SDLWindowPtr sdlWindow, std::string title, int width, int height) noexcept;
	void Destroy() noexcept override;
private:
	SDLWindowPtr sdlWindow;
};

}; // namespace Nibbler::Plugins::SDL
