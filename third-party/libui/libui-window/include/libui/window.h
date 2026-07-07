/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 23:10:50 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/28 01:30:44 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <libui/engine.h>
#include <libui/element.h>
#include <libui/error.h>

#include <libui/window/callbacks.h>
#include <libui/window/driver.h>
#include <libui/window/flags.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ui_window
{
	ui_engine_t				engine;
	ui_window_driver_t		*driver;
	ui_element_t			*root_element; // aka. the Screen

	uint32_t				width;
	uint32_t				height;
	ui_window_callbacks_t	callbacks;
	//TODO: more flags (fullscreen, focused, etc.)
	
	/**
	 * Whether or not the window should ask its driver to handle events.
	 * This is set to false when the window is managed, for example by a
	 * `ui_window_manager_t`.
	 */
	bool					handle_events;

	bool					running;
	bool					is_vsync;

	void					*handle;
}	ui_window_t;

typedef ui_error_t	(*ui_renderer_init_fn)(ui_renderer_t *renderer, ui_window_t *window);

ui_error_t
ui_window_init(
	ui_window_t *window,
	ui_window_driver_t *driver,
	ui_window_params_t params,
	ui_element_t *root_element
);

void
ui_window_destroy(ui_window_t *window);

enum ui_window_tick_result
{
	UI_WINDOW_TICK_OK = 0,
	UI_WINDOW_TICK_CLOSE,
	UI_WINDOW_TICK_ERROR,
};

enum ui_window_tick_result
ui_window_tick(ui_window_t *window);

typedef struct
{
	uint64_t					tick_rate;
	enum ui_window_tick_result	(*tick_hook)(ui_window_t *window, void *data);
	void						*data;
}	ui_window_loop_t;

enum ui_window_tick_result
ui_window_run(ui_window_t *window, ui_window_loop_t params);

#ifdef __cplusplus
}
#endif
