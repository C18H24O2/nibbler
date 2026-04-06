/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FilesystemPluginDiscoverer.hpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 18:53:31 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/06 14:14:08 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Nibbler/Util/Canonical.hpp>
#include <Nibbler/Plugin/IPluginDiscoverer.hpp>

namespace Nibbler::Plugin
{

class FilesystemPluginDiscoverer final : public IPluginDiscoverer
{
public:
	DEFAULT_CANONICAL_MEMBERS(FilesystemPluginDiscoverer)
	constexpr FilesystemPluginDiscoverer(std::filesystem::path root, bool recursive = true) noexcept
		: recursive(recursive), root(std::move(root)) {}

	[[nodiscard]] std::vector<std::filesystem::path> Discover() noexcept override;
private:
	bool recursive;
	std::filesystem::path root;
};

}; // namespace Nibbler::Plugin
