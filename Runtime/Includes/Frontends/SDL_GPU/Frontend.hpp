#ifndef NIBBLER_SDL_GPU_FRONTEND_HPP
#define NIBBLER_SDL_GPU_FRONTEND_HPP

#include <Common/Frontend/Frontend.hpp>
#include <Frontends/SDL_GPU/CompilationProfile.hpp>

namespace Nb::SdlGpu
{
	class NB_SDL_GPU_API SDLGPUFrontend : public Common::Frontend
	{
		public:
			SDLGPUFrontend() = default;
			~SDLGPUFrontend() override = default;

		private:
	};
}

#endif
