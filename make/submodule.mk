# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    submodule.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <contact@dynamicdispat.ch>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/05 02:07:36 by kiroussa          #+#    #+#              #
#    Updated: 2026/03/05 02:08:37 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := $(shell basename $(shell pwd))

SRC_DIR := src
INC_DIR := include
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
DEP_DIR := $(BUILD_DIR)/dep
