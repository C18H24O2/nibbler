/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StandaloneOptions.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 04:23:23 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/25 04:23:42 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Nibbler/Launcher/LaunchOptions.hpp>
#include <Nibbler/Standalone/entrypoint.hpp>

namespace Nibbler::Launcher
{

void StandaloneOptions::CallEntrypoint(Launcher::LaunchOptions& options) const noexcept
{
	Standalone::Entrypoint(options);
}

}; // namespace Nibbler
