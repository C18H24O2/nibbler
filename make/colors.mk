# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    colors.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/07 16:15:45 by kiroussa          #+#    #+#              #
#    Updated: 2026/03/07 16:16:31 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET := $(shell tput sgr0)

# Regular Colors
BLACK := $(shell tput setaf 0)
RED := $(shell tput setaf 1)
GREEN := $(shell tput setaf 2)
YELLOW := $(shell tput setaf 3)
BLUE := $(shell tput setaf 4)
MAGENTA := $(shell tput setaf 5)
CYAN := $(shell tput setaf 6)
WHITE := $(shell tput setaf 7)

# Bold
BOLD := $(shell tput bold)
BBLACK := $(BOLD)$(BLACK)
BRED := $(BOLD)$(RED)
BGREEN := $(BOLD)$(GREEN)
BYELLOW := $(BOLD)$(YELLOW)
BBLUE := $(BOLD)$(BLUE)
BMAGENTA := $(BOLD)$(MAGENTA)
BCYAN := $(BOLD)$(CYAN)
BWHITE := $(BOLD)$(WHITE)

# Underline
UNDERLINE := $(shell tput smul)
UBLACK := $(UNDERLINE)$(BLACK)
URED := $(UNDERLINE)$(RED)
UGREEN := $(UNDERLINE)$(GREEN)
UYELLOW := $(UNDERLINE)$(YELLOW)
UBLUE := $(UNDERLINE)$(BLUE)
UMAGENTA := $(UNDERLINE)$(MAGENTA)
UCYAN := $(UNDERLINE)$(CYAN)
UWHITE := $(UNDERLINE)$(WHITE)

# Background
ON_BLACK := $(shell tput setab 0)
ON_RED := $(shell tput setab 1)
ON_GREEN := $(shell tput setab 2)
ON_YELLOW := $(shell tput setab 3)
ON_BLUE := $(shell tput setab 4)
ON_MAGENTA := $(shell tput setab 5)
ON_CYAN := $(shell tput setab 6)
ON_WHITE := $(shell tput setab 7)

# High Intensity
IBLACK := $(shell tput sitm setaf 0)
IRED := $(shell tput sitm setaf 1)
IGREEN := $(shell tput sitm setaf 2)
IYELLOW := $(shell tput sitm setaf 3)
IBLUE := $(shell tput sitm setaf 4)
IMAGENTA := $(shell tput sitm setaf 5)
ICYAN := $(shell tput sitm setaf 6)
IWHITE := $(shell tput sitm setaf 7)

# Bold High Intensity
BIBLACK := $(IBLACK)$(BOLD)
BIRED := $(IRED)$(BOLD)
BIGREEN := $(IGREEN)$(BOLD)
BIYELLOW := $(IYELLOW)$(BOLD)
BIBLUE := $(IBLUE)$(BOLD)
BIMAGENTA := $(IMAGENTA)$(BOLD)
BICYAN := $(ICYAN)$(BOLD)
BIWHITE := $(IWHITE)$(BOLD)
