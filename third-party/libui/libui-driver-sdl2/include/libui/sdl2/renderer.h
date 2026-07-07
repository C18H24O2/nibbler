/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 04:24:18 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/28 01:31:10 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <libui/window.h>
#include <libui/renderer.h>

#ifdef __cplusplus
extern "C" {
#endif

ui_error_t
ui_renderer_sdl2(void *handle, ui_renderer_t *renderer, ui_window_t *window);

#ifdef __cplusplus
}
#endif
