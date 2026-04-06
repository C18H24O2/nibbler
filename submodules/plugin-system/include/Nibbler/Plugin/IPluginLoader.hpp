/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IPluginLoader.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 18:49:25 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/06 14:08:22 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <expected>
#include <filesystem>
#include <format>
#include <Nibbler/Util/Canonical.hpp>
#include <Nibbler/Plugin/PluginContainer.hpp>

namespace Nibbler::Plugin
{

enum class PluginLoadError
{
	LinkerError,
	SymbolNotFound,
	MissingMetadata,
};

constexpr std::array<std::string_view, 3> PluginLoadErrorStrings = {
	"Linker Error",
	"Symbol not found",
	"Missing metadata",
};

[[nodiscard]] constexpr std::string_view PluginLoadErrorToString(PluginLoadError err) noexcept
{
	return PluginLoadErrorStrings[static_cast<std::size_t>(err)];
}

class IPluginLoader
{
public:
	DEFAULT_CANONICAL_MEMBERS(IPluginLoader)

	[[nodiscard]] virtual std::expected<PluginContainer, PluginLoadError> Load(std::filesystem::path path) noexcept = 0;
	virtual void Unload(PluginContainer& container) noexcept = 0;
protected:
	IPluginLoader() noexcept = default;
};

}; // namespace Nibbler::Plugin

template<>
struct std::formatter<Nibbler::Plugin::PluginLoadError>
{
	constexpr auto parse(std::format_parse_context& ctx)
	{
		return ctx.begin();
	}

	[[nodiscard]] constexpr auto format(const Nibbler::Plugin::PluginLoadError& err, std::format_context& ctx) const
	{
		return std::format_to(ctx.out(), "{}", PluginLoadErrorToString(err));
	}
};
