#include <Frontends/SDL_GPU/Frontend.hpp>
#include <memory>

namespace Nb::SdlGpu
{
}

extern "C"
{
	NB_SDL_GPU_EXPORT Nb::SdlGpu::SDLGPUFrontend* NbFrontendInitialize()
	{
		auto frontend = std::make_unique<Nb::SdlGpu::SDLGPUFrontend>();
		return frontend.release();
	}
}
