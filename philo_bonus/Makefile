# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/18 16:13:11 by lgarfi            #+#    #+#              #
#    Updated: 2024/04/09 17:03:26 by lgarfi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

name = philo_bonus
cc = cc
flags = -Wall -Wextra -Werror -pthread -g3

SRC = $(subst ./src, ./obj, $(shell find ./src -name "*.c" -type f))
OBJ = $(SRC:.c=.o)

OBJ_DIR = $(subst ./src, ./obj, $(shell find ./src/ -type d))
OBJ_DIR_FILE = obj
SRC_DIR = src
HEADER = include/philo_bonus.h

all: $(name)

$(OBJ_DIR_FILE)/%.o: $(SRC_DIR)/%.c $(HEADER) | make_obj_dir
	$(cc) $(flags) -c $< -o $@ -I./include

$(name): $(OBJ) $(HEADER)
	$(cc) $(flags) $(OBJ) -I./include -o $@

make_obj_dir:
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf obj

fclean: clean
	rm -f $(name)

re: fclean all

.PHONY: all clean fclean re
