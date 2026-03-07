# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    functions.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/07 16:35:38 by kiroussa          #+#    #+#              #
#    Updated: 2026/03/07 16:38:03 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

provideModuleOutputFile = $(if $(filter $(FINAL_MODULE),$(1)),$(1).out,lib$(1).so)
provideModuleOutput = $(MODULES_DIR)/$(1)/$(call provideModuleOutputFile,$(1))
taskStart = printf "$(BRED)$(CURRENT_MODULE)$(RESET)$(BBLACK) | $(RESET)"
