# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/17 22:53:31 by kiroussa          #+#    #+#              #
#    Updated: 2026/04/18 00:05:05 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include ../../make/config.mk

TARGET := $(notdir $(shell pwd)).out
SRCS := $(wildcard *.c) $(wildcard *.cpp)
OBJS := $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SRCS)))

DIRS := $(shell $(MAKE) -C ../.. -s include-dirs)
CFLAGS += $(DIRS:%=-I../../%)
CXXFLAGS += $(DIRS:%=-I../../%)
LDFLAGS += -lSDL2 -lSDL2_image -lSDL2_ttf -lm

LIBUI := ../../libui.a

all: $(TARGET)

$(TARGET): $(OBJS) $(LIBUI)
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: $(LIBUI)
$(LIBUI):
	$(MAKE) -C ../..

.PHONY: clean
clean:
	rm -rf $(OBJS)

.PHONY: fclean
fclean: clean
	rm -rf $(TARGET)

re: fclean all
