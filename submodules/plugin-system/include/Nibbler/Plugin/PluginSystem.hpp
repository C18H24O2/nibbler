/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PluginSystem.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:49:55 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/06 14:19:41 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <ranges>
#include <unordered_map>
#include <vector>
#include <string>
#include <string_view>

#include <Nibbler/Util/Identifier.hpp>
#include <Nibbler/Util/NonCopyable.hpp>

#include <Nibbler/Logging/Logger.hpp>
#include <Nibbler/Plugin/IPluginDiscoverer.hpp>
#include <Nibbler/Plugin/IPluginLoader.hpp>
#include <Nibbler/Plugin/Plugin.hpp>

namespace Nibbler::Plugin
{

//TODO: entrypoints system for plugins to communicate with each other

class PluginSystem final : public Util::NonCopyable
{
public:
	constexpr PluginSystem() noexcept
		: logger("PluginSystem") {}

	~PluginSystem() noexcept;

	constexpr void AddDiscoverer(std::shared_ptr<IPluginDiscoverer> discoverer) noexcept
	{
		discoverers.push_back(std::move(discoverer));
	}

	constexpr void AddLoader(std::shared_ptr<IPluginLoader> loader) noexcept
	{
		loaders.push_back(std::move(loader));
	}

	[[nodiscard]] constexpr std::optional<PluginContainer> GetPlugin(const Identifier& id) const
	{
		if (const auto it = plugins.find(id); it != plugins.end())
			return it->second;
		return std::nullopt;
	}

	[[nodiscard]] constexpr std::vector<Identifier> GetLoadedPlugins() const noexcept
	{
		return plugins | std::views::keys | std::ranges::to<std::vector>();
	}

	void LoadPlugins() noexcept;
private:
	std::unordered_map<Identifier, PluginContainer> plugins;
	std::unordered_map<Identifier, std::shared_ptr<IPluginLoader>> pluginIdToLoader;
	std::vector<std::shared_ptr<IPluginDiscoverer>> discoverers;
	std::vector<std::shared_ptr<IPluginLoader>> loaders;
	Logging::Logger logger;
};

}; // namespace Nibbler::Plugin
