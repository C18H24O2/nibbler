/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 00:21:17 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/28 01:30:18 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>

#include <libui/error.h>
#include <libui/renderer.h>
#include <libui/window.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	const char	*title;
	uint32_t	width;
	uint32_t	height;
	uint32_t	flags;
}	ui_window_params_t;

typedef struct ui_window_driver
{
	const char	*name;
	void		*handle;
	void		*(*init)(void);
	void		 (*destroy)(void *handle);
	void		*(*create_window)(void *handle, ui_window_params_t params);
	void		 (*create_window_post)(void *handle, ui_window_t *window);
	void		 (*destroy_window)(void *handle, ui_window_t *window);
	void		 (*delay)(void *handle, uint64_t usecs);
	bool		 (*dispatch_events)(void *handle, ui_window_t *window);
	ui_error_t	 (*create_renderer)(void *handle, ui_renderer_t *renderer_out, ui_window_t *window);
}	ui_window_driver_t;

#ifdef __cplusplus
}
#endif
