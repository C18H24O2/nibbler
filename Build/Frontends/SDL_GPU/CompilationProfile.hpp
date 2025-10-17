#ifndef NIBBLER_FRONTEND_SDLGPU_COMPILATION_PROFILE_HPP
#define NIBBLER_FRONTEND_SDLGPU_COMPILATION_PROFILE_HPP

#include <CompilationProfile.hpp>

#ifdef NB_PLAT_WINDOWS
	#ifdef NB_COMPILER_MSVC
		#ifdef NB_SDL_GPU_BUILD
			#define NB_SDL_GPU_EXPORT __declspec(dllexport)
			#define NB_SDL_GPU_IMPORT __declspec(dllimport)
		#endif
	#elif defined(NB_COMPILER_GCC)
		#ifdef NB_SDL_GPU_BUILD
			#define NB_SDL_GPU_EXPORT __attribute__((dllexport))
			#define NB_SDL_GPU_IMPORT __attribute__((dllimport))
		#endif
	#else
		#define NB_SDL_GPU_EXPORT
		#define NB_SDL_GPU_IMPORT
	#endif

#elif defined(NB_COMPILER_GCC)
	#define NB_SDL_GPU_EXPORT __attribute__((visibility("default")))
	#define NB_SDL_GPU_IMPORT __attribute__((visibility("default")))
#else
	#define NB_SDL_GPU_EXPORT
	#define NB_SDL_GPU_IMPORT
#endif

#ifdef NB_SDL_GPU_BUILD
	#define NB_SDL_GPU_API NB_SDL_GPU_EXPORT
#else
	#define NB_SDL_GPU_API NB_SDL_GPU_IMPORT
#endif

#endif
