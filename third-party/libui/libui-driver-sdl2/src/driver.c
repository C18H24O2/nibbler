/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 00:23:31 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/25 23:43:47 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

#include <libui/window/flags.h> 
#include <libui/sdl2/driver.h>
#include <libui/sdl2/renderer.h>

#define LIBUI_SDL2_INITIAL_RENDER 1

#define unused __attribute__((unused))

static int initialized = 0;

static inline uint32_t
ui_driver_sdl2_flags(uint32_t flags)
{
	uint32_t result = SDL_WINDOW_SHOWN;
	if (flags & UI_WINDOW_FLAG_FULLSCREEN)
		result |= SDL_WINDOW_FULLSCREEN;
	if (flags & UI_WINDOW_FLAG_RESIZABLE)
		result |= SDL_WINDOW_RESIZABLE;
	if (flags & UI_WINDOW_FLAG_BORDERLESS)
		result |= SDL_WINDOW_BORDERLESS;
	if (flags & UI_WINDOW_FLAG_ALWAYS_ON_TOP)
		result |= SDL_WINDOW_ALWAYS_ON_TOP;
	if (flags & UI_WINDOW_FLAG_NO_TASKBAR)
		result |= SDL_WINDOW_SKIP_TASKBAR;
	if (flags & UI_WINDOW_FLAG_HIDDEN)
		result ^= SDL_WINDOW_SHOWN;
	return result;
}

static void
*ui_driver_sdl2_init(void)
{
	if (!initialized)
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0)
			return NULL;
		if (TTF_Init())
			return NULL;
	}
	initialized++;
	return (void *) 1ull;
}

static void
ui_driver_sdl2_destroy(unused void *handle)
{
	if (initialized == 1)
	{
		if (TTF_WasInit())
			TTF_Quit();
		if (SDL_WasInit(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER))
			SDL_Quit();
	}
	if (initialized > 0)
		initialized--;
}

static void
*ui_driver_sdl2_create_window(unused void *handle, ui_window_params_t params)
{
	SDL_Window *window = SDL_CreateWindow(params.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, params.width, params.height, ui_driver_sdl2_flags(params.flags)); 
	if (!window)
		return NULL;
#if LIBUI_SDL2_INITIAL_RENDER
	// Render once to initialize the surface for Wayland compositors
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		SDL_DestroyRenderer(renderer);
	}
#endif
	return (void *) window;
}

static void
ui_driver_sdl2_create_window_post(unused void *handle, ui_window_t *window)
{
	if (window && window->handle)
	{
		SDL_Window *sdl_window = (SDL_Window *) window->handle;
		SDL_SetWindowData(sdl_window, "ui_window", window);
	}
}

static void
ui_driver_sdl2_destroy_window(unused void *handle, ui_window_t *window)
{
	if (window && window->handle)
		SDL_DestroyWindow((SDL_Window *) window->handle);
}

static void
ui_driver_sdl2_delay(unused void *handle, uint64_t usecs)
{
	SDL_Delay((uint32_t) usecs / 1000);
}

static char
*sdl2_strevent(SDL_Event *event)
{
	uint32_t event_type = event->type;
	if (event_type >= SDL_USEREVENT)
		event_type = SDL_USEREVENT;

	switch (event_type)
	{
		case SDL_QUIT:
			return "SDL_QUIT";
		case SDL_LOCALECHANGED:
			return "SDL_LOCALECHANGED";
		case SDL_DISPLAYEVENT:
			return "SDL_DISPLAYEVENT";
		case SDL_WINDOWEVENT:
			switch (event->window.event)
			{
				case SDL_WINDOWEVENT_SHOWN:
					return "SDL_WINDOWEVENT_SHOWN";
				case SDL_WINDOWEVENT_HIDDEN:
					return "SDL_WINDOWEVENT_HIDDEN";
				case SDL_WINDOWEVENT_EXPOSED:
					return "SDL_WINDOWEVENT_EXPOSED";
				case SDL_WINDOWEVENT_MOVED:
					return "SDL_WINDOWEVENT_MOVED";
				case SDL_WINDOWEVENT_RESIZED:
					return "SDL_WINDOWEVENT_RESIZED";
				case SDL_WINDOWEVENT_SIZE_CHANGED:
					return "SDL_WINDOWEVENT_SIZE_CHANGED";
				case SDL_WINDOWEVENT_MINIMIZED:
					return "SDL_WINDOWEVENT_MINIMIZED";
				case SDL_WINDOWEVENT_MAXIMIZED:
					return "SDL_WINDOWEVENT_MAXIMIZED";
				case SDL_WINDOWEVENT_RESTORED:
					return "SDL_WINDOWEVENT_RESTORED";
				case SDL_WINDOWEVENT_ENTER:
					return "SDL_WINDOWEVENT_ENTER";
				case SDL_WINDOWEVENT_LEAVE:
					return "SDL_WINDOWEVENT_LEAVE";
				case SDL_WINDOWEVENT_FOCUS_GAINED:
					return "SDL_WINDOWEVENT_FOCUS_GAINED";
				case SDL_WINDOWEVENT_FOCUS_LOST:
					return "SDL_WINDOWEVENT_FOCUS_LOST";
				case SDL_WINDOWEVENT_CLOSE:
					return "SDL_WINDOWEVENT_CLOSE";
				default:
					return "SDL_WINDOWEVENT_UNKNOWN";
			}
		case SDL_SYSWMEVENT:
			return "SDL_SYSWMEVENT";
		case SDL_KEYDOWN:
			return "SDL_KEYDOWN";
		case SDL_KEYUP:
			return "SDL_KEYUP";
		case SDL_TEXTEDITING:
			return "SDL_TEXTEDITING";
		case SDL_TEXTINPUT:
			return "SDL_TEXTINPUT";
		case SDL_KEYMAPCHANGED:
			return "SDL_KEYMAPCHANGED";
		case SDL_TEXTEDITING_EXT:
			return "SDL_TEXTEDITING_EXT";
		case SDL_MOUSEMOTION:
			return "SDL_MOUSEMOTION";
		case SDL_MOUSEBUTTONDOWN:
			return "SDL_MOUSEBUTTONDOWN";
		case SDL_MOUSEBUTTONUP:
			return "SDL_MOUSEBUTTONUP";
		case SDL_MOUSEWHEEL:
			return "SDL_MOUSEWHEEL";
		case SDL_JOYAXISMOTION:
			return "SDL_JOYAXISMOTION";
		case SDL_JOYBALLMOTION:
			return "SDL_JOYBALLMOTION";
		case SDL_JOYHATMOTION:
			return "SDL_JOYHATMOTION";
		case SDL_JOYBUTTONDOWN:
			return "SDL_JOYBUTTONDOWN";
		case SDL_JOYBUTTONUP:
			return "SDL_JOYBUTTONUP";
		case SDL_JOYDEVICEADDED:
			return "SDL_JOYDEVICEADDED";
		case SDL_JOYDEVICEREMOVED:
			return "SDL_JOYDEVICEREMOVED";
		case SDL_CONTROLLERAXISMOTION:
			return "SDL_CONTROLLERAXISMOTION";
		case SDL_CONTROLLERBUTTONDOWN:
			return "SDL_CONTROLLERBUTTONDOWN";
		case SDL_CONTROLLERBUTTONUP:
			return "SDL_CONTROLLERBUTTONUP";
		case SDL_CONTROLLERDEVICEADDED:
			return "SDL_CONTROLLERDEVICEADDED";
		case SDL_CONTROLLERDEVICEREMOVED:
			return "SDL_CONTROLLERDEVICEREMOVED";
		case SDL_CONTROLLERDEVICEREMAPPED:
			return "SDL_CONTROLLERDEVICEREMAPPED";
		case SDL_FINGERDOWN:
			return "SDL_FINGERDOWN";
		case SDL_FINGERUP:
			return "SDL_FINGERUP";
		case SDL_FINGERMOTION:
			return "SDL_FINGERMOTION";
		case SDL_DOLLARGESTURE:
			return "SDL_DOLLARGESTURE";
		case SDL_DOLLARRECORD:
			return "SDL_DOLLARRECORD";
		case SDL_MULTIGESTURE:
			return "SDL_MULTIGESTURE";
		case SDL_CLIPBOARDUPDATE:
			return "SDL_CLIPBOARDUPDATE";
		case SDL_DROPFILE:
			return "SDL_DROPFILE";
		case SDL_DROPTEXT:
			return "SDL_DROPTEXT";
		case SDL_DROPBEGIN:
			return "SDL_DROPBEGIN";
		case SDL_DROPCOMPLETE:
			return "SDL_DROPCOMPLETE";
		case SDL_AUDIODEVICEADDED:
			return "SDL_AUDIODEVICEADDED";
		case SDL_AUDIODEVICEREMOVED:
			return "SDL_AUDIODEVICEREMOVED";
		case SDL_RENDER_TARGETS_RESET:
			return "SDL_RENDER_TARGETS_RESET";
		case SDL_RENDER_DEVICE_RESET:
			return "SDL_RENDER_DEVICE_RESET";
		case SDL_POLLSENTINEL:
			return "SDL_POLLSENTINEL";
		case SDL_USEREVENT:
			return "SDL_USEREVENT";
		case SDL_LASTEVENT:
			return "SDL_LASTEVENT";
		default:
			return "SDL_UNKNOWN";
	}
	return "SDL_UNKNOWN";
}

static uint32_t
ui_driver_sdl2_event_window_id(SDL_Event *event)
{
	static struct {
		uint32_t type;
		off_t window_field_offset;
	} window_event_types[] = {
#define X(xtype, xstruct) \
		{ .type = xtype, .window_field_offset = offsetof(xstruct, windowID) }
		X(SDL_WINDOWEVENT, SDL_WindowEvent),
		X(SDL_KEYDOWN, SDL_KeyboardEvent),
		X(SDL_KEYUP, SDL_KeyboardEvent),
		X(SDL_TEXTEDITING, SDL_TextEditingEvent),
		X(SDL_TEXTEDITING_EXT, SDL_TextEditingExtEvent),
		X(SDL_TEXTINPUT, SDL_TextInputEvent),
		X(SDL_MOUSEMOTION, SDL_MouseMotionEvent),
		X(SDL_MOUSEBUTTONDOWN, SDL_MouseButtonEvent),
		X(SDL_MOUSEBUTTONUP, SDL_MouseButtonEvent),
		X(SDL_MOUSEWHEEL, SDL_MouseWheelEvent),
		X(SDL_DROPBEGIN, SDL_DropEvent),
		X(SDL_DROPFILE, SDL_DropEvent),
		X(SDL_DROPTEXT, SDL_DropEvent),
		X(SDL_DROPCOMPLETE, SDL_DropEvent),
		X(SDL_USEREVENT, SDL_UserEvent),
#undef X
	};
	uint32_t event_id = event->type;
	if (event_id >= SDL_USEREVENT)
		event_id = SDL_USEREVENT;
	for (size_t i = 0; i < sizeof(window_event_types) / sizeof(window_event_types[0]); i++)
	{
		if (event_id == window_event_types[i].type)
			return *(uint32_t *) ((uint8_t *) event + window_event_types[i].window_field_offset);
	}
	return -1u;
}

static bool
ui_driver_sdl2_event_filter(SDL_Event *event, uint32_t window_id)
{
	if (window_id != 0)
	{
		uint32_t event_window_id = ui_driver_sdl2_event_window_id(event);
		if (event_window_id == -1u)
			return true;
		fprintf(stderr, "ui_driver_sdl2_event_filter: window_id: %u, event_window_id: %u\n", window_id, event_window_id);
		if (event_window_id != window_id)
			return false;
	}
	return true;
}

static void
ui_driver_sdl2_event_handle(SDL_Event *event)
{
	uint32_t window_id = ui_driver_sdl2_event_window_id(event);
	if (window_id == -1u)
	{
		//TODO: global event, handle it, idk how
		fprintf(stderr, "ui_driver_sdl2_event_handle: global event: %s\n", sdl2_strevent(event));
		return;
	}

	fprintf(stderr, "ui_driver_sdl2_event_handle: %s\n", sdl2_strevent(event));
	fprintf(stderr, "ui_driver_sdl2_event_handle: event_window_id: %u\n", window_id);

	SDL_Window *window = SDL_GetWindowFromID(window_id);
	if (!window)
	{
		return;
	}
	fprintf(stderr, "ui_driver_sdl2_event_handle: window: %p\n", window);
	
	ui_window_t *ui_window = (ui_window_t *) SDL_GetWindowData(window, "ui_window");
	if (!ui_window)
	{
		return;
	}
	fprintf(stderr, "ui_driver_sdl2_event_handle: ui_window: %p\n", ui_window);
}

static bool
ui_driver_sdl2_dispatch_events(unused void *handle, ui_window_t *window)
{
	uint32_t window_id = 0;
	if (window)
	{
		window_id = SDL_GetWindowID((SDL_Window *) window->handle);
		if (window_id == 0)
			return false;
	}

	bool has_event = false;
	
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (!has_event)
		{
			has_event = true;
			fprintf(stderr, "ui_driver_sdl2_dispatch_events: window_id: %u\n", window_id);
		}
		if (event.type == SDL_QUIT)
			return false;
		if (ui_driver_sdl2_event_filter(&event, window_id))
			ui_driver_sdl2_event_handle(&event);
	}
	return true;
}

ui_window_driver_t
*ui_driver_sdl2(void)
{
	static ui_window_driver_t driver = {
		.name = "SDL2",
		.init = ui_driver_sdl2_init,
		.destroy = ui_driver_sdl2_destroy,
		.create_window = ui_driver_sdl2_create_window,
		.create_window_post = ui_driver_sdl2_create_window_post,
		.destroy_window = ui_driver_sdl2_destroy_window,
		.delay = ui_driver_sdl2_delay,
		.dispatch_events = ui_driver_sdl2_dispatch_events,
		.create_renderer = ui_renderer_sdl2,
	};
	return &driver;
}
