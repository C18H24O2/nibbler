#ifndef NIBBLER_GLFW_VULKAN_FRONTEND_HPP
#define NIBBLER_GLFW_VULKAN_FRONTEND_HPP

#include <Common/Frontend/Frontend.hpp>

namespace Nb::GLFWVulkan
{
	class GLFWVulkanFrontend : public Common::Frontend
	{
		public:
			GLFWVulkanFrontend() = default;
			~GLFWVulkanFrontend() override = default;

		private:
	};
}

#endif
