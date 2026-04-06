/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:59:31 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/06 13:12:02 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <string_view>

#include <Nibbler/Util/Canonical.hpp>
#include <Nibbler/Util/Identifier.hpp>

namespace Nibbler::Client::Window
{

class Window
{
	public:
		DEFAULT_CANONICAL_MEMBERS(Window);

		virtual void Destroy() noexcept
		{
			if (destroyed)
				return;
			destroyed = true;
		}

		[[nodiscard]] constexpr std::string Title() const noexcept
		{
			return title;
		}

		[[nodiscard]] constexpr int Width() const noexcept
		{
			return width;
		}

		[[nodiscard]] constexpr int Height() const noexcept
		{
			return height;
		}

	protected:
		Window(std::string title, int width, int height) noexcept
			: title(std::move(title)), width(width), height(height) {}

		std::string title;
		int width;
		int height;

		bool destroyed = false;
};

}; // namespace Nibbler::Client::Window
