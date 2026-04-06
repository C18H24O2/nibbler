/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IPluginDiscoverer.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 18:49:26 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/06 14:14:02 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <filesystem>
#include <vector>

#include <Nibbler/Util/Canonical.hpp>

namespace Nibbler::Plugin
{

class IPluginDiscoverer
{
public:
	DEFAULT_CANONICAL_MEMBERS(IPluginDiscoverer)
	
	[[nodiscard]] virtual std::vector<std::filesystem::path> Discover() noexcept = 0;
protected:
	IPluginDiscoverer() noexcept = default;
};


}; // namespace Nibbler::Plugin
