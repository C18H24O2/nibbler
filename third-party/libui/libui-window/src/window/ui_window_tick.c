/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_window_tick.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 03:09:51 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/25 23:43:04 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui/window.h>

enum ui_window_tick_result
ui_window_tick(ui_window_t *window)
{
	if (window->handle_events)
	{
		if (!window->driver->dispatch_events(window->driver->handle, window))
			return UI_WINDOW_TICK_CLOSE;
	}

	window->engine.renderer.begin_frame(window->engine.renderer.handle);
	window->engine.renderer.end_frame(window->engine.renderer.handle);
	return UI_WINDOW_TICK_OK;
}
