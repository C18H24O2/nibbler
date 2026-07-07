/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_window_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 04:37:40 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/25 23:43:18 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui/window.h>

enum ui_window_tick_result
ui_window_run(ui_window_t *window, ui_window_loop_t params)
{
	if (!window)
		return UI_WINDOW_TICK_ERROR;

	window->running = true;
	enum ui_window_tick_result result = UI_WINDOW_TICK_CLOSE;
	while (window->running)
	{
		result = ui_window_tick(window);
		if (result != UI_WINDOW_TICK_OK)
			break;
		if (__builtin_expect(params.tick_rate != 0, 1))
			window->driver->delay(window->driver->handle, params.tick_rate);
	}
	window->running = false;
	ui_window_destroy(window);
	return UI_WINDOW_TICK_CLOSE;
}
