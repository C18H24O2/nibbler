/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entrypoint.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 04:09:52 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/29 08:35:06 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Nibbler/Launcher/LaunchOptions.hpp>

namespace Nibbler::Standalone
{

int Entrypoint(Launcher::LaunchOptions& options);

};
