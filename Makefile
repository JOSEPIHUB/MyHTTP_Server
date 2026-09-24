##
## EPITECH PROJECT, 2026
## ___ Hades_Town ___
## File description:
## Makefile
##

NAME := hell

CXX := g++

BUILD_DIR := .build

CFLAGS := -Wall -Wextra -std=c++20 -lpthread -ggdb3
CFLAGS += -Iinclude

CORE_SRCS := $(wildcard src/*.cpp)
CORE_OBJS := $(CORE_SRCS:src/%.cpp=$(BUILD_DIR)/%.o)

all: $(CORE_OBJS)
	$(CXX) $(CFLAGS) $(CORE_OBJS) -o $(NAME)

$(BUILD_DIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
