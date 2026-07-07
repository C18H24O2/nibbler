# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <contact@dynamicdispat.ch>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/05 01:44:00 by kiroussa          #+#    #+#              #
#    Updated: 2026/07/06 22:35:24 by kiroussa         ###   ########.fr        #
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
all:
	@$(MAKE) -j$(shell nproc) $(FINAL_OUTPUT)

include $(shell find $(SHARED_BUILD_DIR) -type f -name '*.d' 2>/dev/null)

$(SHARED_BUILD_DIR)/%:
	@# @echo "[*] Invalidating $@"
	@if [ $(findstring .c, $<) ] || [ $(findstring .s, $<) ]; then \
		rm -rf $@; \
	fi

$(FINAL_OUTPUT): $(LIB_MODULES_OUTPUT)
	@$(call taskStart,Linking $(BOLD)$@$(RESET)\n)
	@mkdir -p $(BUILD_DIR)
	@for lib in $(MODULES); do \
		(cd $(SHARED_BUILD_DIR); find $$lib/obj -type f -name '*.o' | sort >> $(BUILD_DIR)/objects.txt) \
	done
	@for obj in $$(cat $(BUILD_DIR)/objects.txt); do \
		(cd $(SHARED_BUILD_DIR); cp $$obj $(BUILD_DIR)/$$(echo $$obj | sed 's|^\./||; s|/|_|g'); echo $$obj | sed 's|^\./||; s|/|_|g' >> $(BUILD_DIR)/objects_normalized.txt) \
	done
	@(cd $(BUILD_DIR); $(AR) $(ARFLAGS) $(PROJECT_ROOT)/$(FINAL_OUTPUT) $$(cat $(BUILD_DIR)/objects_normalized.txt))

$(foreach module,$(MODULES),$(eval $(call moduleOutput,$(module))))
$(foreach module,$(MODULES),$(eval $(call moduleDelegate,clean,$(module))))
$(foreach module,$(MODULES),$(eval $(call moduleDelegate,fclean,$(module))))

.PHONY: oclean
oclean:
	@$(call taskStart,Removing build directory $(BOLD)$(SHARED_BUILD_DIR)/$(RESET)\n)
	@rm -rf $(SHARED_BUILD_DIR)

.PHONY: clean
clean: $(LIB_CLEAN_TASKS) oclean

.PHONY: fclean
fclean: $(LIB_FCLEAN_TASKS) oclean
	@$(call taskStart,Removing output $(BOLD)$(FINAL_OUTPUT)$(RESET)\n)
	@rm -f $(FINAL_OUTPUT)

.PHONY: compile_commands.json
compile_commands.json: fclean
	@$(call taskStart,Generating $(BOLD)$@$(RESET)\n)
	@bear -- $(MAKE) -j$(shell nproc)
	@sed -i 's|$(CXX)|$(shell which $(CXX))|g' compile_commands.json

.PHONY: include-dirs
include-dirs:
	@echo $(MODULES:%=%/$(INC_DIR))

.PHONY: re
re: fclean all
