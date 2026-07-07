/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 01:12:39 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/28 01:31:49 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <expected>
#include <memory>
#include <string>
#include <string_view>

#include <libui/window.h>

#include <LibUI/Error.hpp>

namespace LibUI::Window
{

class Window final
{
public:
	~Window(void);
	Window(const Window &) = delete;
	Window(Window &&) = default;
	Window &operator=(const Window &) = delete;
	Window &operator=(Window &&) = default;

	[[nodiscard]] ui_window_tick_result Tick() noexcept;
	ui_window_tick_result Run(ui_window_loop_t params) noexcept;

	[[nodiscard]] static std::expected<Window, LibUI::Error> Create(
		ui_window_driver_t *driver,
		ui_window_params_t params,
		ui_element_t *root_element
	) noexcept;
private:
	Window(ui_window_t window);

	ui_window_t window;
};

};
