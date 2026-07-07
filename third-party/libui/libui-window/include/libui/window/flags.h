/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 02:21:46 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/28 01:30:26 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

enum ui_window_flags
{
	UI_WINDOW_FLAG_FULLSCREEN = 1 << 0,
	UI_WINDOW_FLAG_RESIZABLE = 1 << 1,
	UI_WINDOW_FLAG_BORDERLESS = 1 << 2,
	UI_WINDOW_FLAG_ALWAYS_ON_TOP = 1 << 3,
	UI_WINDOW_FLAG_NO_TASKBAR = 1 << 4,
	UI_WINDOW_FLAG_HIDDEN = 1 << 5,
#define UI_WINDOW_FLAGS_POPUP (UI_WINDOW_FLAG_ALWAYS_ON_TOP | UI_WINDOW_FLAG_NO_TASKBAR)
};

#ifdef __cplusplus
}
#endif
