/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 03:07:08 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/28 01:22:06 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ui_element
{
	struct ui_element	*children;
	uint32_t			children_count;
}	ui_element_t;

#ifdef __cplusplus
}
#endif
