# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/14 11:46:33 by djagusch          #+#    #+#              #
#    Updated: 2023/06/05 13:45:47 by asarikha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COLOURS ###

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

### SET UP ###
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$I \
#	-Wno-unused-but-set-parameter
#	Wno-unused-result


RM = /bin/rm -f
RMDIR = /bin/rmdir -p

LIBFT = libft/libft.a

S = src
O = obj
I = includes

FILES = main \
	ft_builtin \
	ft_error \
	ft_cd \
	ft_echo \
	ft_env \
	ft_export \
	ft_export_printers \
	ft_pwd \
	ft_unset \
	env \
	env_utils \
	free_memory \
	concat \
	lexer \
	lexer_utils \
	token \
	open_files \
	parser \
	parser_utils \
	parser_print \
	token_print \
	exe_child \
	execute \
	find_command \
	redirect \
	pipes \
	syntax_check \
	syntax_utils \
	check_utils \
	here_doc	\
	signals

HEADER = minishell.h libft.h parser.h lexer.h ft_error.h syntax.h
HEADER := $(addprefix $I/,$(HEADER))

SRCS := $(foreach FILE,$(FILES),$(shell find $S -type f -name '$(FILE).c'))
OBJS = $(patsubst $S/%,$O/%,$(SRCS:.c=.o))
O_DIRS = $(dir $(OBJS))

READLINE = -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

NAME = minishell

### RULES ###
all: $(NAME)

print:
	@echo $(PARSER_F)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(READLINE) -Llibft -lft -o $(NAME)
	@echo "$(COLOUR_GREEN) $(NAME) created$(COLOUR_END)"

$O:
	@mkdir -p $@ $(O_DIRS)

$O/%.o: $S/%.c $(HEADER) | $O
	@$(CC) $(CFLAGS) -c $< -o $@

### LIBFT

libft: $(LIBFT)

$(LIBFT):
	@$(MAKE) -C libft
	@echo "$(COLOUR_GREEN) $(LIBFT) created$(COLOUR_END)"

ENV_FILES := $(foreach FILE,$(FILES),$(shell find $S/env -type f -name '$(FILE).c'))

env_test:
	$(CC) $(CFLAGS) $(ENV_FILES) src/builtins/ft_env.c test.c $(HEADER) -Llibft -lft -g

### CLEANING

clean:
	@cd libft && $(MAKE) clean
	@echo "$(COLOUR_RED) $(LIBFT) removed$(COLOUR_END)"
	@$(RM) $(OBJS)
	@if [ -d $O ]; then $(RM) -rf $(O_DIRS) $O; fi

fclean : clean
	@cd libft && $(MAKE) fclean
	@$(RM) $(NAME)
	@echo "$(COLOUR_RED) $(NAME) removed$(COLOUR_END)"

re: fclean $(NAME)

.PHONY: all clean fclean re
