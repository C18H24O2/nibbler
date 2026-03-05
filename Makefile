# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <contact@dynamicdispat.ch>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/05 01:44:00 by kiroussa          #+#    #+#              #
#    Updated: 2026/03/05 02:06:33 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXECUTABLE := nibbler

MODULES_DIR := submodules
MODULES := cli core ui-mlx

provideModuleOutput = $(MODULES_DIR)/$(1)/$(if $(filter $(FINAL_MODULE),$(1)),$(1),lib$(1).so)

FINAL_MODULE := cli
FINAL_MODULE_OUTPUT := $(call provideModuleOutput,$(FINAL_MODULE))

define moduleOutput
$(call provideModuleOutput,$(1)): $(MODULES_DIR)/$(1)/Makefile
	$(MAKE) -C $(MODULES_DIR)/$(1)
endef
define moduleClean
_clean_$(1):
	$(MAKE) -C $(MODULES_DIR)/$(1) clean
endef
define moduleFclean
_fclean_$(1):
	$(MAKE) -C $(MODULES_DIR)/$(1) fclean
endef

all: $(NAME)

$(NAME): $(FINAL_MODULE_OUTPUT)
	ln -sf $(FINAL_MODULE_OUTPUT) $(NAME)

$(foreach module,$(MODULES),$(eval $(call moduleOutput,$(module))))
$(foreach module,$(MODULES),$(eval $(call moduleClean,$(module))))
$(foreach module,$(MODULES),$(eval $(call moduleFclean,$(module))))

oclean:

clean: oclean $(MODULES:%=_clean_%)

fclean: oclean $(MODULES:%=_fclean_%)
	rm -f $(NAME)
