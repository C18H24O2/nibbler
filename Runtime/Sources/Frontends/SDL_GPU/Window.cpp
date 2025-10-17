#include <Frontends/SDL_GPU/Window.hpp>

namespace Nb::SdlGpu
{
	Window::Window(std::uint32_t width, std::uint32_t height, std::string_view title)
	{
		p_window = SDL_CreateWindow(title.data(), width, height, SDL_WINDOW_RESIZABLE);
	}

	Window::~Window()
	{
		if(p_window)
		{
			SDL_DestroyWindow(p_window);
			p_window = nullptr;
		}
	}
}
