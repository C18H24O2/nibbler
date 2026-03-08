# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    submodule.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/05 02:07:36 by kiroussa          #+#    #+#              #
#    Updated: 2026/03/08 02:22:41 by kiroussa         ###   ########.fr        #
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
LDFLAGS += $(if $(filter %.so,$(TARGET)),-shared,)

SRCS := $(shell find $(SRC_DIR) -type f -name '*.cpp')
SRCS := $(patsubst $(SRC_DIR)/%,%,$(SRCS))
OBJS := $(SRCS:%.cpp=%.o)

SRCS := $(addprefix $(SRC_DIR)/,$(SRCS))
OBJS := $(addprefix $(OBJ_DIR)/,$(OBJS))

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	@$(call taskStart)
	@printf "Linking $(BOLD)$(TARGET)$(RESET)\n"
	@$(CXX) $(LDFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(call taskStart)
	@printf "Compiling $(BOLD)$<$(RESET)\n"
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@


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
