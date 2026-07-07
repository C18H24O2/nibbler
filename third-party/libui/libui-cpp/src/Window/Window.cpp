/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 01:18:38 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/28 01:28:08 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utility>

#include <LibUI/Window/Window.hpp>

namespace LibUI::Window
{

Window::Window(ui_window_t window)
	: window(std::move(window))
{
}

Window::~Window(void)
{
	ui_window_destroy(&window);
}

ui_window_tick_result Window::Tick() noexcept
{
	return ui_window_tick(&window);
}

ui_window_tick_result Window::Run(ui_window_loop_t params) noexcept
{
	return ui_window_run(&window, params);
}

std::expected<Window, LibUI::Error> Window::Create(
	ui_window_driver_t *driver,
	ui_window_params_t params,
	ui_element_t *root_element
) noexcept {
	ui_window_t window;
	auto error = ui_window_init(&window, driver, params, root_element);
	if (error != UI_ERROR_OK)
		return std::unexpected(static_cast<LibUI::Error>(error));
	return Window(std::move(window));
}

};
