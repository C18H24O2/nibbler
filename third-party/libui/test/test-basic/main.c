/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 23:03:14 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/26 03:31:50 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui/engine.h>
#include <libui/window.h>
#include <libui/window/manager.h>
#include <libui/sdl2/driver.h>
#include <libui/sdl2/renderer.h>
#include <stdio.h>
#include <unistd.h>

#define defer(func) __attribute__((cleanup(func)))
#define expect(msg, ...) do { \
	ui_error_t error = __VA_ARGS__; \
	if (error != UI_ERROR_OK) \
	{ \
		fprintf(stderr, "error in %s: %s\n", msg, ui_strerror(error)); \
		return 1; \
	} \
} while (0)

static enum ui_window_tick_result
tick(ui_window_t *window, void *data)
{
	(void) data;
	ui_engine_t *engine = &window->engine;
	fprintf(stderr, "tick!\n");
	//TODO: tick all elements starting from the root node
	(void) engine;
	(void) window;
	return UI_WINDOW_TICK_OK;
}

int main(void)
{
	fprintf(stderr, "Hello, world!\n");

	// ui_window_manager_t manager;
	// expect("libui window manager init", ui_wm_init(&manager,

	defer(ui_window_destroy) ui_window_t window;
	expect("libui window init", ui_window_init(&window, ui_driver_sdl2(), (ui_window_params_t) {
		.title = "libui test",
		.width = 640,
		.height = 480,
		.flags = UI_WINDOW_FLAG_RESIZABLE,
	}, NULL));

	//TODO: input handler

	ui_window_run(&window, (ui_window_loop_t) {
		.tick_rate = 1000000 / 60,
		.tick_hook = tick,
		.data = NULL,
	});

	return 0;
}
