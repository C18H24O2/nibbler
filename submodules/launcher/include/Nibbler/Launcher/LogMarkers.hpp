/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LogMarkers.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 03:01:29 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/25 03:09:29 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Nibbler/Logging/LogMarker.hpp>

namespace Nibbler::Launcher::LogMarkers
{

using namespace Nibbler::Logging;

static constexpr LogMarker base{"launcher"};
static constexpr LogMarker argparse{"arguments", &base};

}; // namespace Nibbler::Launcher::LogMarkers
