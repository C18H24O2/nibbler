/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_window_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 02:20:40 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/28 01:25:17 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include <libui/engine.h>
#include <libui/error.h>
#include <libui/window.h>

ui_error_t
ui_window_init(
	ui_window_t *window,
	ui_window_driver_t *driver,
	ui_window_params_t params,
	ui_element_t *root_element
) {
	if (!window || !driver)
		return UI_ERROR_NULLPTR;
	memset(window, 0, sizeof(ui_window_t));
	window->handle_events = true;

	window->root_element = root_element;
	window->width = params.width;
	window->height = params.height;

	ui_error_t error = UI_ERROR_DRIVER;

	window->driver = driver;
	if (!driver->handle)
		driver->handle = driver->init();
	if (!driver->handle)
		goto ret;

	window->handle = driver->create_window(driver->handle, params);
	if (!window->handle)
		goto destroy_driver_handle;

	error = ui_engine_init(&window->engine);
	if (error != UI_ERROR_OK)
		goto destroy_window_handle;

	error = driver->create_renderer(driver->handle, &window->engine.renderer, window);
	if (error != UI_ERROR_OK)
		goto destroy_engine;

	// window->fullscreen = params.flags & UI_WINDOW_FLAG_FULLSCREEN;
	// window->focused = true;

	return UI_ERROR_OK;

destroy_engine:
	ui_engine_destroy(&window->engine);
destroy_window_handle:
	if (window->handle)
		driver->destroy_window(driver->handle, window->handle);
destroy_driver_handle:
	driver->destroy(driver->handle);
ret:
	return error;
}
