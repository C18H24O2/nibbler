/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WindowProvider.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 20:11:51 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/06 13:47:07 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>

#include <Nibbler/Util/Canonical.hpp>
#include <Nibbler/Util/Identifier.hpp>
#include <Nibbler/Registry/RegistryKey.hpp>
#include <Nibbler/Client/Window/Window.hpp>

namespace Nibbler::Client::Window
{

class WindowProvider
{
public:
	DEFAULT_CANONICAL_MEMBERS(WindowProvider)

	[[nodiscard]] virtual std::unique_ptr<Window> CreateWindow(const std::string& title, int width, int height) = 0;

	static constexpr Registry::RegistryKey<WindowProvider> REGISTRY_KEY = {
		*Util::Identifier::From("nibbler", "window/provider")
	};
protected:
	WindowProvider() = default;
};

}; // namespace Nibbler::Client::Window
