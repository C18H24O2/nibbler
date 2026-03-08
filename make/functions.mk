# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    functions.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/07 16:35:38 by kiroussa          #+#    #+#              #
#    Updated: 2026/03/08 02:22:00 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include $(PROJECT_ROOT)/make/colors.mk
ifeq ($(SHARED_BUILD_DIR),)
include $(PROJECT_ROOT)/make/config.mk
endif

moduleWidth = $(shell printf "%s" "$(1)" | wc -L)
MAX_MODULE_NAME_WIDTH := $(shell printf "%s" "$(MODULES)" | tr ' ' '\n' | awk '{ if (length > max) { max = length } } END { print max }')
padded = $(shell printf "%$(MAX_MODULE_NAME_WIDTH)s" "$(1)")

provideModuleOutputFile = $(if $(filter $(FINAL_MODULE),$(1)),$(1).out,lib$(1).so)
provideModuleOutput = $(SHARED_BUILD_DIR)/$(1)/$(call provideModuleOutputFile,$(1))
taskStart = printf "$(BRED)$(call padded,$(CURRENT_MODULE))$(RESET)$(BBLACK) | $(RESET)"
