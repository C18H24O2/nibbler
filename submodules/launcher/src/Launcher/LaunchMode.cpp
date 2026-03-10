/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LaunchMode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 01:30:23 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/10 11:36:55 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Nibbler/Launcher/LaunchOptions.hpp>

namespace Nibbler::Launcher
{

bool LaunchMode::operator==(LaunchMode a) const noexcept
{
	return value == a.value;
}

bool LaunchMode::operator==(LaunchMode::Value a) const noexcept
{
	return value == a;
}

bool LaunchMode::operator!=(LaunchMode a) const noexcept
{
	return value != a.value;
}

bool LaunchMode::operator!=(LaunchMode::Value a) const noexcept
{
	return value != a;
}

std::optional<LaunchOptions> LaunchMode::DelegateParse(int argc, char **argv) const noexcept
{
	switch (value)
	{
		default:
			return std::nullopt;
	}
}

std::string_view LaunchMode::GetName() const noexcept
{
	return names[static_cast<size_t>(value)];
}

std::optional<LaunchMode> LaunchMode::FromString(std::string_view name) noexcept
{
	for (auto i = 0u; i < names.size(); i++)
		if (name == names[i])
			return LaunchMode{static_cast<LaunchMode::Value>(i)};
	return std::nullopt;
}

}; // namespace Nibbler
