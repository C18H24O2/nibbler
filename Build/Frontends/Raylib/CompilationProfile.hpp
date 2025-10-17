#ifndef NIBBLER_FRONTEND_RAYLIB_COMPILATION_PROFILE_HPP
#define NIBBLER_FRONTEND_RAYLIB_COMPILATION_PROFILE_HPP

#include <CompilationProfile.hpp>

#ifdef NB_PLAT_WINDOWS
	#ifdef NB_COMPILER_MSVC
		#ifdef NB_RAYLIB_BUILD
			#define NB_RAYLIB_EXPORT __declspec(dllexport)
			#define NB_RAYLIB_IMPORT __declspec(dllimport)
		#endif
	#elif defined(NB_COMPILER_GCC)
		#ifdef NB_RAYLIB_BUILD
			#define NB_RAYLIB_EXPORT __attribute__((dllexport))
			#define NB_RAYLIB_IMPORT __attribute__((dllimport))
		#endif
	#else
		#define NB_RAYLIB_EXPORT
		#define NB_RAYLIB_IMPORT
	#endif

#elif defined(NB_COMPILER_GCC)
	#define NB_RAYLIB_EXPORT __attribute__((visibility("default")))
	#define NB_RAYLIB_IMPORT __attribute__((visibility("default")))
#else
	#define NB_RAYLIB_EXPORT
	#define NB_RAYLIB_IMPORT
#endif

#ifdef NB_RAYLIB_BUILD
	#define NB_RAYLIB_API NB_RAYLIB_EXPORT
#else
	#define NB_RAYLIB_API NB_RAYLIB_IMPORT
#endif

#endif
