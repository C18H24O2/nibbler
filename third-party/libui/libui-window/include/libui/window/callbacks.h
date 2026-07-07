/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 03:11:30 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/28 01:30:11 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>

#include <libui/error.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ui_window ui_window_t;

typedef struct
{
	void	(*on_key)(ui_window_t *window, uint32_t key, uint32_t scancode, int32_t action, void *data);
	void	(*on_mouse)(ui_window_t *window, uint32_t button, uint32_t action, void *data);
	void	(*on_resize)(ui_window_t *window, uint32_t width, uint32_t height, void *data);
	void	(*on_fullscreen)(ui_window_t *window, int32_t fullscreen, void *data);
	void	(*on_focus)(ui_window_t *window, int32_t focused, void *data);
}	ui_window_callbacks_t;

#ifdef __cplusplus
}
#endif
