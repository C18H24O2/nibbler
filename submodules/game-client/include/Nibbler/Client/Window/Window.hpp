/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:59:31 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/27 20:16:47 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Nibbler/Util/Canonical.hpp>

namespace Nibbler::Client::Window
{

class Window
{
	public:
		DEFAULT_CANONICAL_MEMBERS(Window);

		[[nodiscard]] virtual std::string Title() const = 0;
		[[nodiscard]] virtual int Width() const = 0;
		[[nodiscard]] virtual int Height() const = 0;

	protected:
		Window() = default;
};

}; // namespace Nibbler::Client::Window
