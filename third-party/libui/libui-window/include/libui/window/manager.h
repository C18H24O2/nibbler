/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 13:59:07 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/28 01:34:22 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <libui/error.h>
#include <libui/window.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	ui_window_driver_t *driver;
	ui_renderer_init_fn *renderer_init;

	ui_window_t *windows;
	uint32_t window_count;
}	ui_window_manager_t;

ui_error_t
ui_wm_init(ui_window_manager_t *manager, ui_window_driver_t *driver, ui_renderer_init_fn *renderer_init);

void
ui_wm_destroy(ui_window_manager_t *manager);

void
ui_wm_tick(ui_window_manager_t *manager);

void
ui_wm_run(ui_window_manager_t *manager, ui_window_loop_t params);

#ifdef __cplusplus
}
#endif
