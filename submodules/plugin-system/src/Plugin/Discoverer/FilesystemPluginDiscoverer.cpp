/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FilesystemPluginDiscoverer.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 19:03:26 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/06 14:14:15 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Nibbler/Util/Concat.hpp>
#include <Nibbler/Util/Typename.hpp>
#include <Nibbler/Logging/Logger.hpp>
#include <Nibbler/Plugin/Discoverer/FilesystemPluginDiscoverer.hpp>

namespace Nibbler::Plugin
{

constexpr std::string_view PLATFORM_EXTENSION = 
#if defined(_WIN32)
	".dll"
#elif defined(__APPLE__)
	".dylib"
#else
	".so"
#endif
;
constexpr std::string_view PLATFORM_PREFIX =
#if defined(_WIN32)
	""
#elif defined(__APPLE__)
	"lib"
#else
	"lib"
#endif
;

constexpr std::string_view PLUGIN_PROJECT_NAME = "nibbler";
constexpr std::string_view PLUGIN_PREFIX_PART = "plug-";
constexpr std::string_view PLUGIN_PREFIX = Util::concat_v<PLATFORM_PREFIX, PLUGIN_PROJECT_NAME, PLUGIN_PREFIX_PART>;

constexpr std::string_view PLUGIN_EXTENSION = PLATFORM_EXTENSION;

Logging::Logger logger(Util::Typename<FilesystemPluginDiscoverer>());

std::vector<std::filesystem::path> FilesystemPluginDiscoverer::Discover() noexcept
{
	logger.Debug().Emit("Discovering plugins {}from '{}'", recursive ? "recursively " : "", root.string());

	std::vector<std::filesystem::path> plugins;
	for (const auto& entry : std::filesystem::recursive_directory_iterator(root))
	{
		if (entry.is_regular_file())
		{
			auto path = entry.path().filename().string();
			if (path.starts_with(PLUGIN_PREFIX) && path.ends_with(PLUGIN_EXTENSION))
			{
				logger.Trace().Emit("Found plugin candidate {}", entry.path().filename().string());
				plugins.push_back(entry.path());
			}
		}
	}

	logger.Debug().Emit("Found {} plugin candidates", plugins.size());
	return plugins;
}

}; // namespace Nibbler::Plugin
