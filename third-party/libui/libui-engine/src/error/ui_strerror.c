/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_strerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 23:21:02 by kiroussa          #+#    #+#             */
/*   Updated: 2026/04/18 00:36:37 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui/error.h>
#include <stddef.h>

const char	*ui_strerror(ui_error_t error)
{
	static const char *messages[] = {
		[UI_ERROR_OK] = "No error",
		[UI_ERROR_NULLPTR] = "Null pointer",
		[UI_ERROR_ALLOC] = "Memory allocation error",
		[UI_ERROR_DRIVER] = "Driver error occured",
	};

	if (error < UI_ERROR_MIN || error > UI_ERROR_MAX)
		return "Unknown error";
	return messages[error];
}
