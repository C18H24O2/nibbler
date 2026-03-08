# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/07 16:36:43 by kiroussa          #+#    #+#              #
#    Updated: 2026/03/08 02:15:49 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXECUTABLE := nibbler
MAKE := make --debug=none --no-print-directory

CXX := clang++
CXXFLAGS := -Wall -Wextra -std=c++23
ifeq ($(DEBUG),1)
CXXFLAGS += -ggdb -g3 -O0
else
CXXFLAGS += -Werror -O2
endif
#TODO: link against everything under the sun
LDFLAGS := 

SRC_DIR := src
INC_DIR := include
MODULES_DIR := submodules
THIRD_PARTY_DIR := third-party
ifeq ($(shell pwd),$(PROJECT_ROOT))
SHARED_BUILD_DIR := build
else
SHARED_BUILD_DIR := $(PROJECT_ROOT)/build
endif
BUILD_DIR := $(SHARED_BUILD_DIR)/$(MODULE_NAME)
OBJ_DIR := $(BUILD_DIR)/obj
DEP_DIR := $(BUILD_DIR)/dep

MODULES := cli core ui-mlx

include $(PROJECT_ROOT)/make/functions.mk

FINAL_MODULE := cli
FINAL_MODULE_OUTPUT := $(call provideModuleOutput,$(FINAL_MODULE))
