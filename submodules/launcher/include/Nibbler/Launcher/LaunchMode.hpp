/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LaunchMode.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 00:23:57 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/10 17:48:28 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <array>
#include <optional>
#include <string_view>

#include <Nibbler/Launcher/LaunchOptions.hpp>

namespace Nibbler::Launcher
{

class LaunchMode
{
public:
	enum Value
	{
		STANDALONE,
		CLIENT,
		SERVER,
	};
	constexpr LaunchMode() = default;
	constexpr LaunchMode(Value aLaunchMode) noexcept : value(aLaunchMode) {}

	explicit operator bool() const = delete;
	[[nodiscard]] bool operator==(LaunchMode a) const noexcept;
	[[nodiscard]] bool operator==(Value a) const noexcept;
	[[nodiscard]] bool operator!=(LaunchMode a) const noexcept;
	[[nodiscard]] bool operator!=(Value a) const noexcept;

	[[nodiscard]] std::optional<LaunchOptions> DelegateParse(int argc, char **argv) const noexcept;
	[[nodiscard]] std::string_view GetName() const noexcept;

	[[nodiscard]] static std::optional<LaunchMode> FromString(std::string_view name) noexcept;

	template <typename T>
	static std::optional<LaunchOptions> DelegateParse(int argc, char **argv) noexcept { 
	}

private:
	Value value;

	static constexpr std::array<std::string_view, 3> names{"standalone", "client", "server"};
};

}; // namespace Nibbler
