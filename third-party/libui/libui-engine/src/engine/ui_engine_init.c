/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_engine_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 23:24:41 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/28 01:11:30 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include <libui/engine.h>

ui_error_t
ui_engine_init(ui_engine_t *engine)
{
	if (!engine)
		return UI_ERROR_NULLPTR;
	memset(engine, 0, sizeof(ui_engine_t));
	return UI_ERROR_OK;
}
