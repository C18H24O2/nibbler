/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 04:04:00 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/26 01:40:13 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include <SDL2/SDL_render.h>

#include <libui/sdl2/renderer.h>

static void
ui_renderer_sdl2_destroy(void *handle)
{
	SDL_DestroyRenderer((SDL_Renderer *) handle);
}

static void
ui_renderer_sdl2_begin_frame(void *handle)
{
	SDL_Renderer *renderer = (SDL_Renderer *) handle;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

static void
ui_renderer_sdl2_end_frame(void *handle)
{
	SDL_Renderer *renderer = (SDL_Renderer *) handle;
	SDL_RenderPresent(renderer);
}

static void
ui_renderer_sdl2_toggle_vsync(void *handle, bool enabled)
{
	SDL_Renderer *renderer = (SDL_Renderer *) handle;
	SDL_RenderSetVSync(renderer, enabled);
	SDL_Window *window = SDL_RenderGetWindow(renderer);
	if (window)
	{
		ui_window_t *ui_window = (ui_window_t *) SDL_GetWindowData(window, "ui_window");
		if (ui_window)
			ui_window->is_vsync = enabled;
	}
}

static void
ui_renderer_sdl2_draw_rect(void *handle, const ui_rect_t rect, const ui_color_t color)
{
	SDL_Renderer *renderer = (SDL_Renderer *) handle;
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_Rect sdl_rect = (SDL_Rect) { .x = rect.x, .y = rect.y, .w = rect.w, .h = rect.h };
	SDL_RenderDrawRect(renderer, &sdl_rect);
}

static void
ui_renderer_sdl2_draw_line(void *handle, const ui_pos2d_t pos1, const ui_pos2d_t pos2, const ui_color_t color)
{
	SDL_Renderer *renderer = (SDL_Renderer *) handle;
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(renderer, pos1.x, pos1.y, pos2.x, pos2.y);
}

ui_error_t
ui_renderer_sdl2(void *handle, ui_renderer_t *renderer, ui_window_t *window)
{
	static ui_renderer_t vtable = {
		.handle = NULL,
		.destroy = ui_renderer_sdl2_destroy,
		.begin_frame = ui_renderer_sdl2_begin_frame,
		.end_frame = ui_renderer_sdl2_end_frame,
		.text_width = NULL,
		.text_height = NULL,
		.draw_text = NULL,
		.draw_rect = ui_renderer_sdl2_draw_rect,
		.draw_line = ui_renderer_sdl2_draw_line,
		.draw_image = NULL,
		.draw_image_uv = NULL,
		.toggle_vsync = ui_renderer_sdl2_toggle_vsync,
	};

	(void) handle;
	if (!renderer || !window)
		return UI_ERROR_NULLPTR;
	memset(renderer, 0, sizeof(ui_renderer_t));
	memcpy(renderer, &vtable, sizeof(ui_renderer_t));

	renderer->handle = SDL_CreateRenderer(window->handle, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer->handle)
		return UI_ERROR_DRIVER;

	return UI_ERROR_OK;
}
