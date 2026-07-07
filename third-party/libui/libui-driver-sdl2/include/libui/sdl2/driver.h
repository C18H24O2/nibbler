/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 00:04:12 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/28 01:31:21 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <libui/window.h>

#ifdef __cplusplus
extern "C" {
#endif

ui_window_driver_t
*ui_driver_sdl2(void);

#ifdef __cplusplus
}
#endif
