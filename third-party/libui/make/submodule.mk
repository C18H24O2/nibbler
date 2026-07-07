# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    submodule.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/05 02:07:36 by kiroussa          #+#    #+#              #
#    Updated: 2026/04/17 23:04:33 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT_ROOT ?= $(patsubst %/,%,$(dir $(patsubst %/,%,$(shell pwd))))
NAME := $(shell basename $(shell pwd))
CURRENT_MODULE := $(NAME)
MODULE_NAME := $(NAME)

-include ../make/development.mk
include ../make/config.mk

include ../make/colors.mk
include ../make/functions.mk

TARGET := $(call provideModuleOutput,$(CURRENT_MODULE))
TARGET_NAME := $(call provideModuleOutputFile,$(CURRENT_MODULE))

SRCS := $(shell find $(SRC_DIR) -type f -name '*.c' -o -name '*.cpp')
SRCS := $(patsubst $(SRC_DIR)/%,%,$(SRCS))
OBJS := $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SRCS)))

SRCS := $(addprefix $(SRC_DIR)/,$(SRCS))
OBJS := $(addprefix $(OBJ_DIR)/,$(OBJS))

TARGET_DEPS = $(OBJS)

.PHONY: all
all: $(TARGET)

$(TARGET): $(TARGET_DEPS)
	@$(call taskStart,Linking $(BOLD)$(TARGET_NAME)$(RESET)\n)
	@$(AR) $(ARFLAGS) $(TARGET) $(OBJS)
	@echo "$(TARGET): $^ $(PROJECT_ROOT)/$(MODULES_DIR)/$(CURRENT_MODULE)/Makefile" > $(DEP_DIR)/module.d

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(call taskStart,Compiling $(BOLD)$<$(RESET)\n)
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $(DEP_DIR)/$*.tmp.d)
	@$(CC) $(CFLAGS) $(DFLAGS) -c $(CWD)/$< -o $@
	@mv $(DEP_DIR)/$*.tmp.d $(DEP_DIR)/$*.d
	@touch $(DEP_DIR)/$*.d

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(call taskStart,Compiling $(BOLD)$<$(RESET)\n)
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $(DEP_DIR)/$*.tmp.d)
	@$(CXX) $(CXXFLAGS) $(DFLAGS) -c $(CWD)/$< -o $@
	@mv $(DEP_DIR)/$*.tmp.d $(DEP_DIR)/$*.d
	@touch $(DEP_DIR)/$*.d

.PHONY: clean
clean:
	@$(call taskStart,Removing $(BOLD)$(BUILD_DIR)$(RESET)\n)
	@rm -rf $(BUILD_DIR)

.PHONY: fclean
fclean: clean
	@$(call taskStart,Removing $(BOLD)$(TARGET)$(RESET)\n)
	@rm -f $(TARGET)
