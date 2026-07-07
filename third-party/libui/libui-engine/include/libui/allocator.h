/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 03:02:30 by kiroussa          #+#    #+#             */
/*   Updated: 2026/07/07 03:02:57 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

typedef struct ui_allocator
{
	void	*data;
	void	*(*alloc)(struct ui_allocator *self, size_t size);
	void	(*free)(struct ui_allocator *self, void *ptr);
	void	*(*realloc)(struct ui_allocator *self, void *ptr, size_t size);
}	ui_allocator_t;

#ifdef __cplusplus
}
#endif
