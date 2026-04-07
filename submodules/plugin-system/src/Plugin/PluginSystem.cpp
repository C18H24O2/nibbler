/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PluginSystem.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 17:05:05 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/07 03:17:09 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <chrono>
#include <filesystem>
#include <string_view>
#include <Nibbler/Util/Concat.hpp>
#include <Nibbler/Plugin/PluginSystem.hpp>

using namespace std::chrono;

namespace Nibbler::Plugin
{

PluginSystem::~PluginSystem() noexcept
{
	logger.Debug().Emit("Unloading {} plugin{}", plugins.size(), plugins.size() == 1 ? "" : "s");
	for (auto& [id, loader] : pluginIdToLoader)
	{
		logger.Trace().Emit("Shutting down plugin {}", id.ToString());
		plugins[id].plugin->Shutdown(*this);
		logger.Trace().Emit("Unloading plugin {}", id.ToString());
		loader->Unload(plugins[id]);
		plugins.erase(id);
	}
}

void PluginSystem::LoadPlugins() noexcept
{
	logger.Debug().Emit("Starting loading plugins");

	std::vector<std::filesystem::path> paths;
	if (discoverers.empty())
		logger.Warn().Emit("No discoverers registered");
	else
	{
		for (auto& discoverer : discoverers)
		{
			auto discovered = discoverer->Discover();
			logger.Trace().Emit("Discoverer {} returned {} plugin candidates", (void *) discoverer.get(), discovered.size());
			std::move(discovered.begin(), discovered.end(), std::back_inserter(paths));
		}
		logger.Debug().Emit("Discovered {} plugin candidates", paths.size());
	}

	if (loaders.empty())
		logger.Warn().Emit("No loaders registered");
	else
	{
		for (auto loader : loaders)
		{
			for (auto& path : paths)
			{
				auto start = steady_clock::now();
				auto tryLoad = loader->Load(path);
				auto end = steady_clock::now();
				if (!tryLoad)
				{
					logger.Error().Emit("Failed to load plugin {}: {}", path.string(), tryLoad.error());
					continue;
				}
				auto container = *tryLoad;
				auto id = container.metadata.id;
				if (plugins.contains(id))
				{
					logger.Error().Emit("Failed to load plugin {}: plugin with id {} already loaded", path.string(), id.ToString());
					loader->Unload(container);
					continue;
				}
				logger.Spam().Emit("Took {}ms to load plugin {}", duration_cast<milliseconds>(end - start).count(), id.ToString());
				logger.Trace().Emit("Loaded plugin {}, initializing...", id.ToString());
				start = steady_clock::now();
				bool result = container.plugin->Init(*this);
				end = steady_clock::now();
				if (!result)
				{
					logger.Error().Emit("Failed to initialize plugin {}", id.ToString());
					logger.Trace().Emit("Shutting down plugin {}", id.ToString());
					container.plugin->Shutdown(*this);
					logger.Trace().Emit("Unloading plugin {}", id.ToString());
					loader->Unload(container);
					continue;
				}
				logger.Spam().Emit("Took {}ms to initialize plugin {}", duration_cast<milliseconds>(end - start).count(), id.ToString());
				logger.Trace().Emit("Initialized plugin {}", id.ToString());

				plugins.insert({id, container});
				pluginIdToLoader.insert({id, loader});

			}
		}
	}
}

}; // namespace Nibbler::Plugin
