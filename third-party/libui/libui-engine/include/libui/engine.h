/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 23:12:42 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/28 01:13:18 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <libui/error.h>
#include <libui/input.h>
#include <libui/renderer.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	ui_renderer_t		renderer;
	ui_input_handler_t	input_handler;
}	ui_engine_t;

ui_error_t
ui_engine_init(ui_engine_t *engine);

void
ui_engine_destroy(ui_engine_t *engine);

#ifdef __cplusplus
}
#endif
