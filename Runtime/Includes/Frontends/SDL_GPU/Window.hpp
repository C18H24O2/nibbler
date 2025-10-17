#ifndef NIBBLER_SDL_GPU_WINDOW_HPP
#define NIBBLER_SDL_GPU_WINDOW_HPP

#include <Common/Frontend/Frontend.hpp>
#include <Common/Utils/NonCopyable.h>
#include <Frontends/SDL_GPU/CompilationProfile.hpp>

#include <string_view>

#include <SDL3/SDL.h>

namespace Nb::SdlGpu
{
	class NB_SDL_GPU_API Window : public Common::NonCopyable
	{
		public:
			~Window();

		private:
			Window(std::uint32_t width, std::uint32_t height, std::string_view title);

		private:
			SDL_Window* p_window = nullptr;
	};

	
}

#endif
