# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/07 16:36:43 by kiroussa          #+#    #+#              #
#    Updated: 2026/04/28 01:21:09 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FINAL_OUTPUT := libui.a
MAKE := make --debug=none --no-print-directory
CWD := $(shell pwd)

CC := clang
CXX := clang++
CFLAGS := -Wall -Wextra -std=c23 -fPIC
CXXFLAGS := -Wall -Wextra -std=c++23 -fPIC
ifeq ($(DEBUG),1)
CFLAGS += -ggdb -g3
CXXFLAGS += -ggdb -g3
else
CFLAGS += -Werror -O2
CXXFLAGS += -Werror -O2
endif
LDFLAGS :=

AR := ar
ARFLAGS := rcs

DFLAGS = -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.tmp.d

SRC_DIR := src
INC_DIR := include

ifdef PROJECT_ROOT
MODULES_DIR := .
THIRD_PARTY_DIR := third-party
SHARED_BUILD_DIR := $(PROJECT_ROOT)/build
BUILD_DIR := $(SHARED_BUILD_DIR)/$(MODULE_NAME)
OBJ_DIR := $(BUILD_DIR)/obj
DEP_DIR := $(BUILD_DIR)/dep

MODULES ?= $(shell find $(PROJECT_ROOT)/$(MODULES_DIR) -maxdepth 1 -mindepth 1 -type d -name 'libui-*' -exec basename {} \; | LC_ALL=C sort 2>/dev/null)

include $(PROJECT_ROOT)/make/functions.mk

LIB_MODULES_OUTPUT := $(foreach module,$(MODULES),$(call provideModuleOutput,$(module)))
CFLAGS += $(MODULES:%=-I$(PROJECT_ROOT)/$(MODULES_DIR)/%/$(INC_DIR))
CXXFLAGS += $(MODULES:%=-I$(PROJECT_ROOT)/$(MODULES_DIR)/%/$(INC_DIR))
endif
