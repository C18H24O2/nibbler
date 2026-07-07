# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/07 16:36:43 by kiroussa          #+#    #+#              #
#    Updated: 2026/07/07 02:14:01 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXECUTABLE := nibbler
MAKE := make --debug=none --no-print-directory
CWD := $(shell pwd)

ifndef PROJECT_ROOT
$(error PROJECT_ROOT is not set)
endif

CXX := clang++
CXXFLAGS := -Wall -Wextra -std=c++23 -fPIC
ifeq ($(DEBUG),1)
CXXFLAGS += -ggdb -g3
else
CXXFLAGS += -Werror -O2
endif

DFLAGS = -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.tmp.d
#TODO: ideally the sdl3 dep should be discovered in plug-sdl/Makefile
LDFLAGS := -latomic -lSDL3 

SRC_DIR := src
INC_DIR := include
MODULES_DIR := submodules
THIRD_PARTY_DIR := third-party
SHARED_BUILD_DIR := $(PROJECT_ROOT)/build
BUILD_DIR := $(SHARED_BUILD_DIR)/$(MODULE_NAME)
OBJ_DIR := $(BUILD_DIR)/obj
DEP_DIR := $(BUILD_DIR)/dep

FINAL_MODULE := launcher
MODULES := $(shell find $(PROJECT_ROOT)/$(MODULES_DIR) -maxdepth 1 -mindepth 1 -type d -exec basename {} \; | LC_ALL=C sort 2>/dev/null)

include $(PROJECT_ROOT)/make/functions.mk

PLUGIN_MODULES := $(filter plug-%,$(MODULES))

FINAL_MODULE_OUTPUT := $(call provideModuleOutput,$(FINAL_MODULE))
LIB_MODULES := $(filter-out $(FINAL_MODULE),$(MODULES))
LIB_MODULES_OUTPUT := $(foreach module,$(LIB_MODULES),$(call provideModuleOutput,$(module)))
LIB_MODULES_NOPLUG := $(filter-out $(PLUGIN_MODULES),$(LIB_MODULES))
LIB_MODULES_NOPLUG_OUTPUT := $(foreach module,$(LIB_MODULES_NOPLUG),$(call provideModuleOutput,$(module)))


CXXFLAGS += -I$(PROJECT_ROOT)/$(MODULES_DIR)/$(CURRENT_MODULE)/$(INC_DIR)

LIB_MODULES_OTHER := $(filter-out $(CURRENT_MODULE),$(MODULES))
NO_PLUGINS_MODULES := $(filter-out $(PLUGIN_MODULES),$(MODULES))
CXXFLAGS += $(NO_PLUGINS_MODULES:%=-I$(PROJECT_ROOT)/$(MODULES_DIR)/%/$(INC_DIR))

# libraries
LIBRARIES := $(shell find $(PROJECT_ROOT)/$(THIRD_PARTY_DIR) -maxdepth 1 -mindepth 1 -type d | LC_ALL=C sort 2>/dev/null)
define __declareLibraryVars
DYNMAKE_LIBS += $(1)
DYNMAKE_LIB_$(1)_NAME := $(1)
DYNMAKE_LIB_$(1)_OUTPUT := $(2)
endef
define declareLibrary
$(eval $(call __declareLibraryVars,$(1),$(2)))
endef

LIBRARIES_DYNMAKE_DECL_FILES := $(LIBRARIES:%=%/lib.dyn.mk)
$(foreach file,$(LIBRARIES_DYNMAKE_DECL_FILES),$(eval include $(file)))
LDFLAGS += $(EXTRA_LDFLAGS)

define declareLibraryRules
ifeq ($(DEBUG),1)
.PHONY: $(PROJECT_ROOT)/$(THIRD_PARTY_DIR)/$(1)/$(2)
endif
$(PROJECT_ROOT)/$(THIRD_PARTY_DIR)/$(1)/$(2):
	@$(call taskStart,Building $(BOLD)$(1)$(RESET) library $(BOLD)$(2)$(RESET)\n)
	@$(MAKE) -C $(PROJECT_ROOT)/$(THIRD_PARTY_DIR)/$(1) MAX_MODULE_NAME_WIDTH=$(MAX_MODULE_NAME_WIDTH)
LIB_DEPS_OUTPUT += $(PROJECT_ROOT)/$(THIRD_PARTY_DIR)/$(1)/$(2)

.PHONY: __clean_lib_$(1)
__clean_lib_$(1):
	@$(call taskStart,Cleaning $(BOLD)$(1)$(RESET) library $(BOLD)$(2)$(RESET)\n)
	@$(MAKE) -C $(PROJECT_ROOT)/$(THIRD_PARTY_DIR)/$(1) clean MAX_MODULE_NAME_WIDTH=$(MAX_MODULE_NAME_WIDTH)
LIB_CLEAN_TASKS += __clean_lib_$(1)

.PHONY: __fclean_lib_$(1)
__fclean_lib_$(1):
	@$(call taskStart,Cleaning $(BOLD)$(1)$(RESET) library $(BOLD)$(2)$(RESET)\n)
	@$(MAKE) -C $(PROJECT_ROOT)/$(THIRD_PARTY_DIR)/$(1) fclean MAX_MODULE_NAME_WIDTH=$(MAX_MODULE_NAME_WIDTH)
LIB_FCLEAN_TASKS += __fclean_lib_$(1)
endef
