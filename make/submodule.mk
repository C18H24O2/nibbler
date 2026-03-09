# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    submodule.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/05 02:07:36 by kiroussa          #+#    #+#              #
#    Updated: 2026/03/09 03:00:28 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT_ROOT ?= $(patsubst %/,%,$(dir $(patsubst %/,%,$(dir $(patsubst %/,%,$(shell pwd))))))
NAME := $(shell basename $(shell pwd))
CURRENT_MODULE := $(NAME)
MODULE_NAME := $(NAME)

-include ../../make/development.mk
include ../../make/config.mk

include ../../make/colors.mk
include ../../make/functions.mk

TARGET := $(call provideModuleOutput,$(CURRENT_MODULE))
TARGET_NAME := $(call provideModuleOutputFile,$(CURRENT_MODULE))

LDFLAGS += $(if $(filter %.so,$(TARGET)),-shared,)

SRCS := $(shell find $(SRC_DIR) -type f -name '*.cpp')
SRCS := $(patsubst $(SRC_DIR)/%,%,$(SRCS))
OBJS := $(SRCS:%.cpp=%.o)

SRCS := $(addprefix $(SRC_DIR)/,$(SRCS))
OBJS := $(addprefix $(OBJ_DIR)/,$(OBJS))

TARGET_DEPS := $(OBJS)
ifeq ($(MODULE_NAME),$(FINAL_MODULE))
TARGET_DEPS += $(LIB_MODULES_OUTPUT)
endif

.PHONY: all
all: $(TARGET)

$(TARGET): $(TARGET_DEPS)
	@$(call taskStart)
	@printf "Linking $(BOLD)$(TARGET_NAME)$(RESET)\n"
	@$(CXX) -o $@ $^ $(LDFLAGS)
	@echo "$(TARGET): $^ $(PROJECT_ROOT)/$(MODULES_DIR)/$(CURRENT_MODULE)/Makefile" > $(DEP_DIR)/module.d

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(call taskStart)
	@printf "Compiling $(BOLD)$<$(RESET)\n"
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $(DEP_DIR)/$*.tmp.d)
	$(CXX) $(CXXFLAGS) $(DFLAGS) -c $(CWD)/$< -o $@
	@mv $(DEP_DIR)/$*.tmp.d $(DEP_DIR)/$*.d
	@touch $(DEP_DIR)/$*.d

.PHONY: clean
clean:
	@$(call taskStart)
	@printf "Removing $(BOLD)$(BUILD_DIR)$(RESET)\n"
	@rm -rf $(BUILD_DIR)

.PHONY: fclean
fclean: clean
	@$(call taskStart)
	@printf "Removing $(BOLD)$(TARGET)$(RESET)\n"
	@rm -f $(TARGET)
