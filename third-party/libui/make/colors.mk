# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    colors.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/07 16:15:45 by kiroussa          #+#    #+#              #
#    Updated: 2026/03/08 22:16:42 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TPUT := tput 
RESET := $(shell $(TPUT) sgr0)

# Regular Colors
BLACK := $(shell $(TPUT) setaf 0)
RED := $(shell $(TPUT) setaf 1)
GREEN := $(shell $(TPUT) setaf 2)
YELLOW := $(shell $(TPUT) setaf 3)
BLUE := $(shell $(TPUT) setaf 4)
MAGENTA := $(shell $(TPUT) setaf 5)
CYAN := $(shell $(TPUT) setaf 6)
WHITE := $(shell $(TPUT) setaf 7)

# Bold
BOLD := $(shell $(TPUT) bold)
BBLACK := $(BOLD)$(BLACK)
BRED := $(BOLD)$(RED)
BGREEN := $(BOLD)$(GREEN)
BYELLOW := $(BOLD)$(YELLOW)
BBLUE := $(BOLD)$(BLUE)
BMAGENTA := $(BOLD)$(MAGENTA)
BCYAN := $(BOLD)$(CYAN)
BWHITE := $(BOLD)$(WHITE)

# Underline
UNDERLINE := $(shell $(TPUT) smul)
UBLACK := $(UNDERLINE)$(BLACK)
URED := $(UNDERLINE)$(RED)
UGREEN := $(UNDERLINE)$(GREEN)
UYELLOW := $(UNDERLINE)$(YELLOW)
UBLUE := $(UNDERLINE)$(BLUE)
UMAGENTA := $(UNDERLINE)$(MAGENTA)
UCYAN := $(UNDERLINE)$(CYAN)
UWHITE := $(UNDERLINE)$(WHITE)

# Background
ON_BLACK := $(shell $(TPUT) setab 0)
ON_RED := $(shell $(TPUT) setab 1)
ON_GREEN := $(shell $(TPUT) setab 2)
ON_YELLOW := $(shell $(TPUT) setab 3)
ON_BLUE := $(shell $(TPUT) setab 4)
ON_MAGENTA := $(shell $(TPUT) setab 5)
ON_CYAN := $(shell $(TPUT) setab 6)
ON_WHITE := $(shell $(TPUT) setab 7)

# High Intensity
IBLACK := $(shell $(TPUT) sitm setaf 0)
IRED := $(shell $(TPUT) sitm setaf 1)
IGREEN := $(shell $(TPUT) sitm setaf 2)
IYELLOW := $(shell $(TPUT) sitm setaf 3)
IBLUE := $(shell $(TPUT) sitm setaf 4)
IMAGENTA := $(shell $(TPUT) sitm setaf 5)
ICYAN := $(shell $(TPUT) sitm setaf 6)
IWHITE := $(shell $(TPUT) sitm setaf 7)

# Bold High Intensity
BIBLACK := $(IBLACK)$(BOLD)
BIRED := $(IRED)$(BOLD)
BIGREEN := $(IGREEN)$(BOLD)
BIYELLOW := $(IYELLOW)$(BOLD)
BIBLUE := $(IBLUE)$(BOLD)
BIMAGENTA := $(IMAGENTA)$(BOLD)
BICYAN := $(ICYAN)$(BOLD)
BIWHITE := $(IWHITE)$(BOLD)
