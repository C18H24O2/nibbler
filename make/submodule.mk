# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    submodule.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <contact@dynamicdispat.ch>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/05 02:07:36 by kiroussa          #+#    #+#              #
#    Updated: 2026/03/07 17:32:16 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT_ROOT := $(
NAME := $(shell basename $(shell pwd))
CURRENT_MODULE := $(NAME)

-include ../../make/development.mk

include ../../make/colors.mk
include ../../make/config.mk
include ../../make/functions.mk

FINAL_MODULE := cli
FINAL_MODULE_OUTPUT := $(call provideModuleOutput,$(FINAL_MODULE))
