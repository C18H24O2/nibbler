# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <contact@dynamicdispat.ch>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/05 01:44:00 by kiroussa          #+#    #+#              #
#    Updated: 2026/03/07 17:32:19 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include ./make/config.mk
include ./make/colors.mk
include ./make/submodule/functions.mk

CURRENT_MODULE := <root>
PROJECT_ROOT := $(shell pwd)
MODULES := cli core ui-mlx

define moduleOutput
$(call provideModuleOutput,$(1)): $(MODULES_DIR)/$(1)/Makefile
	@$(MAKE) -C $(MODULES_DIR)/$(1)
endef
define moduleDelegate
_$(1)_$(2):
	@$(MAKE) -C $(MODULES_DIR)/$(1) $(2)
endef

all: $(EXECUTABLE)

$(EXECUTABLE): $(FINAL_MODULE_OUTPUT)
	@$(call taskStart)
	@printf "Linking $(BOLD)$<$(RESET) to $(BOLD)$@$(RESET).\n"
	@ln -sf $< $@

$(foreach module,$(MODULES),$(eval $(call moduleOutput,$(module))))
$(foreach module,$(MODULES),$(eval $(call moduleDelegate,clean,$(module))))
$(foreach module,$(MODULES),$(eval $(call moduleDelegate,fclean,$(module))))

oclean:

clean: oclean $(MODULES:%=_clean_%)

fclean: oclean # $(MODULES:%=_fclean_%)
	@$(call taskStart)
	@printf "Removing $(BOLD)./$(EXECUTABLE)$(RESET).\n"
	@rm -f $(EXECUTABLE)
