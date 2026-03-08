# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <contact@dynamicdispat.ch>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/05 01:44:00 by kiroussa          #+#    #+#              #
#    Updated: 2026/03/08 02:22:29 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT_ROOT := $(shell pwd)
CURRENT_MODULE := <root>
MODULE_NAME := root

include ./make/config.mk
include ./make/colors.mk
include ./make/functions.mk

define moduleOutput
$(call provideModuleOutput,$(1)): $(MODULES_DIR)/$(1)/Makefile
	@$(MAKE) -C $(MODULES_DIR)/$(1)
endef
define moduleDelegate
$(1)_$(2):
	@$(MAKE) -C $(MODULES_DIR)/$(2) $(1)
endef

.PHONY: all
all: $(EXECUTABLE)

$(EXECUTABLE): $(FINAL_MODULE_OUTPUT)
	@$(call taskStart)
	@printf "Linking $(BOLD)$<$(RESET) to $(BOLD)$@$(RESET).\n"
	@ln -sf $< $@

$(foreach module,$(MODULES),$(eval $(call moduleOutput,$(module))))
$(foreach module,$(MODULES),$(eval $(call moduleDelegate,clean,$(module))))
$(foreach module,$(MODULES),$(eval $(call moduleDelegate,fclean,$(module))))

.PHONY: clean
clean: # $(MODULES:%=clean_%)
	@$(call taskStart)
	@printf "Removing build directory $(BOLD)$(SHARED_BUILD_DIR)/$(RESET).\n"
	@rm -rf $(SHARED_BUILD_DIR)

.PHONY: fclean
fclean: clean # $(MODULES:%=fclean_%)
	@$(call taskStart)
	@printf "Removing executable $(BOLD)$(EXECUTABLE)$(RESET).\n"
	@rm -f $(EXECUTABLE)

.PHONY: re
re: fclean all
