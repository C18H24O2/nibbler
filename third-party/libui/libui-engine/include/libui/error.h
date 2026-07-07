/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 23:14:26 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/28 01:13:32 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum ui_error
{
#define UI_ERROR_MIN	UI_ERROR_OK
#define UI_ERROR_MAX	_UI_ERROR_MAX
	UI_ERROR_OK = 0,
	UI_ERROR_NULLPTR,
	UI_ERROR_ALLOC,
	UI_ERROR_DRIVER,
	_UI_ERROR_MAX,
};

typedef enum ui_error ui_error_t;

#define unwrap(...) do { \
	ui_error_t error = __VA_ARGS__; \
	if (error != UI_ERROR_OK) \
		return error; \
} while (0)

const char	*ui_strerror(ui_error_t error);

#ifdef __cplusplus
}
#endif
