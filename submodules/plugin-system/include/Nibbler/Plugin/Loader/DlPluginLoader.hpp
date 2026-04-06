/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DlPluginLoader.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 19:30:26 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/06 11:01:54 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Nibbler/Util/Canonical.hpp>
#include <Nibbler/Plugin/IPluginLoader.hpp>

namespace Nibbler::Plugin
{

class DlPluginLoader final : public IPluginLoader
{
public:
	DEFAULT_CANONICAL_MEMBERS(DlPluginLoader);
	constexpr DlPluginLoader() noexcept = default;

	[[nodiscard]] std::expected<PluginContainer, PluginLoadError> Load(std::filesystem::path path) noexcept override;
	void Unload(PluginContainer& container) noexcept override;
private:
	
};

}; // namespace Nibbler::Plugin
