# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/29 23:25:19 by marvin            #+#    #+#              #
#    Updated: 2024/05/08 18:05:57 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# This is a minimal set of ANSI/VT100 color codes
_END=\033[0;0m
_BOLD=\033[0;1m
_UNDER=\033[0;4m
_REV=\033[0;7m

# Colors
_GREY=\033[0;30m
_RED=\033[0;31m
_GREEN=\033[0;32m
_YELLOW=\033[0;33m
_BLUE=\033[0;34m
_PURPLE=\033[0;35m
_CYAN=\033[0;36m
_WHITE=\033[0;37m

# Inverted, i.e. colored backgrounds
_IGREY=\033[0;40m
_IRED=\033[0;41m
_IGREEN=\033[0;42m
_IYELLOW=\033[0;43m
_IBLUE=\033[0;44m
_IPURPLE=\033[0;45m
_ICYAN=\033[0;46m
_IWHITE=\033[0;47m

# Color test
_ROSE=\x1b[38;5;213m
_NEW_BLUE=\x1b[38;5;80m
_NEW_YELLOW=\x1b[38;5;228m
_GREEN_BOLD=\033[1;32m
_LIGHT_GREY=\x1b[38;5;242m

MAKEFLAGS += --no-print-directory
OPTIONS_PRINTED = /tmp/options_printed

SRC = \
	args_manage.c \
	finish_conditions.c \
	init_struct.c \
	main.c \
	thread.c

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
NAME = philo
RM = rm -rf
CC = cc
CFLAGS = -Wall -Wextra -Werror
INC = -I./headers

all : $(NAME)

print_options : $(OPTIONS_PRINTED)

$(OPTIONS_PRINTED) :
	@ /bin/bash -c "echo"
	@ /bin/bash -c "echo -e \"$(_ROSE)Compiling options$(_END) :  $(CC) $(CFLAGS)\""
	@ /bin/bash -c "echo"
	@ touch $(OPTIONS_PRINTED)

$(NAME) : $(OPTIONS_PRINTED) $(OBJ_DIR) $(OBJ)
	@ /bin/bash -c "echo"
	@ /bin/bash -c "echo -e \"$(_NEW_BLUE)Linking files creating binary $(NAME)$(_END)\""
	@ /bin/bash -c "echo -e \"$(CC) $(CFLAGS) $(notdir $(OBJ))\""
	@ $(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@ /bin/bash -c "echo"
	@ /bin/bash -c "echo -e \"$(_GREEN_BOLD)[DONE]$(_END)\"" 

$(OBJ_DIR) :
	@ mkdir -p $@

$(OBJ_DIR)/%.o: %.c
	@ /bin/bash -c "printf \"$(_BLUE)Compiling$(_END) %-21s --> %-21s\n\" $(notdir $<) $(notdir $@)"
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $(INC) -c $< -o $@

clean :
	@ /bin/bash -c "echo -e \"$(_LIGHT_GREY)Cleaning object files$(_END)\""
	@ $(RM) $(OBJ_DIR)
	@ $(RM) $(OPTIONS_PRINTED)

fclean : clean
	@ /bin/bash -c "echo -e \"$(_LIGHT_GREY)Cleaning binary$(_END)\""
	@ $(RM) $(NAME)

re : fclean all
