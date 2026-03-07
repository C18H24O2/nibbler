# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/07 16:36:43 by kiroussa          #+#    #+#              #
#    Updated: 2026/03/07 16:38:55 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXECUTABLE := nibbler

CXX := clang++
CXXFLAGS := -Wall -Wextra -std=c++23
ifeq ($(DEBUG),1)
CXXFLAGS += -ggdb -g3 -O0
else
CXXFLAGS += -Werror -O2
endif

SRC_DIR := src
INC_DIR := include
MODULES_DIR := submodules
THIRD_PARTY_DIR := third-party
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
DEP_DIR := $(BUILD_DIR)/dep
