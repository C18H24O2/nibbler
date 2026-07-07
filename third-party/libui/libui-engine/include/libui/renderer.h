/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 23:11:50 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/28 01:14:20 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <libui/font.h>
#include <libui/image.h>
#include <libui/prims.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	void	*handle;
	void	(*destroy)(void *handle);

	void	(*begin_frame)(void *handle);
	void	(*end_frame)(void *handle);

	size_t	(*text_width)(void *handle, const ui_font_t *font, const char *text);
	size_t	(*text_height)(void *handle, const ui_font_t *font, const char *text);
	void	(*draw_text)(void *handle, const ui_font_t *font, const char *text, const ui_pos2d_t pos, const ui_color_t color);
	void	(*draw_rect)(void *handle, const ui_rect_t rect, const ui_color_t color);
	void	(*draw_line)(void *handle, const ui_pos2d_t pos1, const ui_pos2d_t pos2, ui_color_t color);
	void	(*draw_image)(void *handle, const ui_image_t *image, const ui_rect_t rect);
	void	(*draw_image_uv)(void *handle, const ui_image_t *image, const ui_rect_t rect, ui_rect_t uv);

	void	(*toggle_vsync)(void *handle, bool enabled);
}	ui_renderer_t;

#ifdef __cplusplus
}
#endif
