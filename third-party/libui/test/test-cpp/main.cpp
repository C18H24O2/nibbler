/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 23:04:57 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/28 01:31:49 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <print>

#include <libui/sdl2/driver.h>
#include <LibUI/Window/Window.hpp>

using namespace LibUI::Window;

int main(void)
{
	std::println(stderr, "Hello, World!");

	auto window = Window::Create(ui_driver_sdl2(), {
		.title = "libui test",
		.width = 640,
		.height = 480,
		.flags = UI_WINDOW_FLAG_RESIZABLE,
	}, nullptr);

	if (!window)
		return 1;

	window->Run({
		.tick_rate = 1000000 / 60,
		.tick_hook = [](ui_window_t *window, void *data) {
			(void) data;
			ui_engine_t *engine = &window->engine;
			std::println(stderr, "tick!");
			//TODO: tick all elements starting from the root node
			(void) engine;
			(void) window;
			return UI_WINDOW_TICK_OK;
		},
		.data = nullptr,
	});

	return 0;
}
