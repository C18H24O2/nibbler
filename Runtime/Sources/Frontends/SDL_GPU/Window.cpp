#include <Frontends/SDL_GPU/Window.hpp>

namespace Nb::SdlGpu
{
	Window::Window(const std::uint32_t width, const std::uint32_t height, const std::string_view title)
	{
		p_window = SDL_CreateWindow(title.data(), width, height, SDL_WINDOW_RESIZABLE);
	}

	Window::~Window()
	{
		if (p_window)
		{
			SDL_DestroyWindow(p_window);
			p_window = nullptr;
		}
	}
}
