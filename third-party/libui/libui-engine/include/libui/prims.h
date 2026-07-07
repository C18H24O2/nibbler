/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prims.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 04:10:39 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/28 01:14:11 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	uint16_t	x;
	uint16_t	y;
}	ui_pos2d_t;

#define UI_POS2D(x, y) ((ui_pos2d_t) { .x = x, .y = y })

typedef struct
{
	union
	{
		struct
		{
			uint16_t	x;
			uint16_t	y;
		};
		ui_pos2d_t	pos1;
	};
	ui_pos2d_t	pos2;
	union
	{
		struct
		{
			uint16_t	w;
			uint16_t	h;
		};
		ui_pos2d_t	size;
	};
}	ui_rect_t;

#define UI_RECT_ABS(x1, y1, x2, y2) \
	((ui_rect_t) { \
		.pos1 = { .x = x1, .y = y1 }, \
		.pos2 = { .x = x2, .y = y2 }, \
		.size = { .x = x2 - x1, .y = y2 - y1 } \
	})
#define UI_RECT(x, y, w, h) \
	((ui_rect_t) { \
		.pos1 = { .x = x, .y = y }, \
		.pos2 = { .x = x + w, .y = y + h }, \
		.size = { .x = w, .y = h } \
	})


typedef union
{
	struct 	
	{
		uint8_t	a;
		uint8_t	r;
		uint8_t	g;
		uint8_t	b;
	};
	uint32_t	argb;
	uint8_t		argb_arr[4];
}	ui_color_t;

#define UI_COLOR(val) ((ui_color_t) { .argb = val })
#define UI_COLOR_ARGB(a, r, g, b) ((ui_color_t) { .a = a, .r = r, .g = g, .b = b })

#ifdef __cplusplus
}
#endif
