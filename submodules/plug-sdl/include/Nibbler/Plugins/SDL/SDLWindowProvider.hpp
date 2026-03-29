/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDLWindowProvider.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:57:53 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/28 13:13:06 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>

#include <Nibbler/Util/Identifier.hpp>
#include <Nibbler/Client/Window/WindowProvider.hpp>

namespace Nibbler::Plugins::SDL
{

class SDLWindowProvider: public Client::Window::WindowProvider
{
	SDLWindowProvider() noexcept = default;
	[[nodiscard]] std::unique_ptr<Client::Window::Window> CreateWindow(const std::string& title, int width, int height) override;

	static constexpr Util::Identifier ID = *Util::Identifier::From("nibbler", "window/provider/sdl");
};

}; // namespace Nibbler::Plugins::SDL
