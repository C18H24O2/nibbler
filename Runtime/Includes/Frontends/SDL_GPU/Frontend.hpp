#ifndef NIBBLER_SDLGPU_FRONTEND_HPP
#define NIBBLER_SDLGPU_FRONTEND_HPP

#include <Common/Frontend/Frontend.hpp>

namespace Nb::SdlGpu
{
	class SDLGPUFrontend : public Common::Frontend
	{
		public:
			SDLGPUFrontend() = default;
			~SDLGPUFrontend() override = default;

		private:
	};
}

#endif
