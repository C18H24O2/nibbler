#ifndef NIBBLER_FRONTEND_GLFW_VULKAN_COMPILATION_PROFILE_HPP
#define NIBBLER_FRONTEND_GLFW_VULKAN_COMPILATION_PROFILE_HPP

#include <CompilationProfile.hpp>

#ifdef NB_PLAT_WINDOWS
	#ifdef NB_COMPILER_MSVC
		#ifdef NB_GLFW_VULKAN_BUILD
			#define NB_GLFW_VULKAN_EXPORT __declspec(dllexport)
			#define NB_GLFW_VULKAN_IMPORT __declspec(dllimport)
		#endif
	#elif defined(NB_COMPILER_GCC)
		#ifdef NB_GLFW_VULKAN_BUILD
			#define NB_GLFW_VULKAN_EXPORT __attribute__((dllexport))
			#define NB_GLFW_VULKAN_IMPORT __attribute__((dllimport))
		#endif
	#else
		#define NB_GLFW_VULKAN_EXPORT
		#define NB_GLFW_VULKAN_IMPORT
	#endif

#elif defined(NB_COMPILER_GCC)
	#define NB_GLFW_VULKAN_EXPORT __attribute__((visibility("default")))
	#define NB_GLFW_VULKAN_IMPORT __attribute__((visibility("default")))
#else
	#define NB_GLFW_VULKAN_EXPORT
	#define NB_GLFW_VULKAN_IMPORT
#endif

#ifdef NB_GLFW_VULKAN_BUILD
	#define NB_GLFW_VULKAN_API NB_GLFW_VULKAN_EXPORT
#else
	#define NB_GLFW_VULKAN_API NB_GLFW_VULKAN_IMPORT
#endif

#endif
