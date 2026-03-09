# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <contact@dynamicdispat.ch>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/05 01:44:00 by kiroussa          #+#    #+#              #
#    Updated: 2026/03/09 01:11:40 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT_ROOT := $(shell pwd)
CURRENT_MODULE := <root>
MODULE_NAME := root

include ./make/config.mk
include ./make/colors.mk
include ./make/functions.mk

define moduleOutput
ifeq ($(1),$(FINAL_MODULE))
$(call provideModuleOutput,$(1)): $(MODULES_DIR)/$(1)/Makefile $(LIB_MODULES_OUTPUT)
else
$(call provideModuleOutput,$(1)): $(MODULES_DIR)/$(1)/Makefile
endif
	@$(MAKE) -C $(MODULES_DIR)/$(1)
endef
define moduleDelegate
$(1)_$(2):
	@$(MAKE) -C $(MODULES_DIR)/$(2) $(1)
endef

.PHONY: all
all: $(EXECUTABLE)

include $(shell find $(SHARED_BUILD_DIR) -type f -name '*.d' 2>/dev/null)

$(SHARED_BUILD_DIR)/%:
	@# @echo "[*] Invalidating $@"
	@if [ $(findstring .c, $<) ] || [ $(findstring .s, $<) ]; then \
		rm -rf $@; \
	fi

$(EXECUTABLE): $(FINAL_MODULE_OUTPUT)
	@$(call taskStart)
	@printf "Linking $(BOLD)$<$(RESET) to $(BOLD)$@$(RESET)\n"
	@ln -sf $< $@

$(foreach module,$(MODULES),$(eval $(call moduleOutput,$(module))))
$(foreach module,$(MODULES),$(eval $(call moduleDelegate,clean,$(module))))
$(foreach module,$(MODULES),$(eval $(call moduleDelegate,fclean,$(module))))

.PHONY: clean
clean: # $(MODULES:%=clean_%)
	@$(call taskStart)
	@printf "Removing build directory $(BOLD)$(SHARED_BUILD_DIR)/$(RESET)\n"
	@rm -rf $(SHARED_BUILD_DIR)

.PHONY: fclean
fclean: clean # $(MODULES:%=fclean_%)
	@$(call taskStart)
	@printf "Removing executable $(BOLD)$(EXECUTABLE)$(RESET)\n"
	@rm -f $(EXECUTABLE)

.PHONY: compile_commands.json
compile_commands.json:
	@$(call taskStart)
	@printf "Generating $(BOLD)$@$(RESET)\n"
	@bear -- $(MAKE) re

.PHONY: re
re: fclean all
