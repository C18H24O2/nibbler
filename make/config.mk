# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/07 16:36:43 by kiroussa          #+#    #+#              #
#    Updated: 2026/03/25 04:12:24 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXECUTABLE := nibbler
MAKE := make --debug=none --no-print-directory
CWD := $(shell pwd)

CXX := clang++
CXXFLAGS := -Wall -Wextra -std=c++23 -fPIC
ifeq ($(DEBUG),1)
CXXFLAGS += -ggdb -g3
else
CXXFLAGS += -Werror -O2
endif

DFLAGS = -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.tmp.d
#TODO: link against third-party libs
LDFLAGS := -latomic

SRC_DIR := src
INC_DIR := include
MODULES_DIR := submodules
THIRD_PARTY_DIR := third-party
SHARED_BUILD_DIR := $(PROJECT_ROOT)/build
BUILD_DIR := $(SHARED_BUILD_DIR)/$(MODULE_NAME)
OBJ_DIR := $(BUILD_DIR)/obj
DEP_DIR := $(BUILD_DIR)/dep

FINAL_MODULE := launcher
MODULES := $(FINAL_MODULE) core ui-mlx logging game-client game-standalone game-server

include $(PROJECT_ROOT)/make/functions.mk

FINAL_MODULE_OUTPUT := $(call provideModuleOutput,$(FINAL_MODULE))
LIB_MODULES := $(filter-out $(FINAL_MODULE),$(MODULES))
LIB_MODULES_OUTPUT := $(foreach module,$(LIB_MODULES),$(call provideModuleOutput,$(module)))

CXXFLAGS += -I$(PROJECT_ROOT)/$(MODULES_DIR)/$(CURRENT_MODULE)/$(INC_DIR)

LIB_MODULES_OTHER := $(filter-out $(CURRENT_MODULE),$(MODULES))
CXXFLAGS += $(LIB_MODULES_OTHER:%=-I$(PROJECT_ROOT)/$(MODULES_DIR)/%/$(INC_DIR))
