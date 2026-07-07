/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_window_destroy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 02:38:24 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/18 13:57:19 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui/window.h>

void
ui_window_destroy(ui_window_t *window)
{
	if (!window)
		return ;
	if (window->driver->handle)
		window->driver->destroy_window(window->driver->handle, window->handle);
	window->handle = NULL;
}
