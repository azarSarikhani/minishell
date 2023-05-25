# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/14 11:46:33 by djagusch          #+#    #+#              #
#    Updated: 2023/05/24 10:50:16 by asarikha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COLOURS ###

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

### SET UP ###
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$I

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
	count_commands \
	do_child \
	execute \
	find_command \
	redirect \
	utils \
	syntax_check \
	syntax_utils \
	check_utils \
	here_doc

HEADER = minishell.h libft.h parser.h lexer.h ft_error.h syntax.h
HEADER := $(addprefix $I/,$(HEADER))

SRCS := $(foreach FILE,$(FILES),$(shell find $S -type f -name '$(FILE).c'))
OBJS = $(patsubst $S/%,$O/%,$(SRCS:.c=.o))
O_DIRS = $(dir $(OBJS))

READLINE = -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

NAME = minishell

PARSER_F := $(shell find $S/parser -type f -name '*.c')
BUILTIN_F = $(shell find $S/builtins -type f -name '*.c')
ENV_F = $(shell find $S/env -type f -name '*.c')
REDIR_F = $(shell find $S/redir_exec -type f -name '*.c')

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

parser_test: $(LIBFT) $(PARSER_F) src/printing/parser_print.c src/free_memory/free_memory.c src/ft_error.c src/tests/parser_test.c
	@$(CC) $(CFLAGS) src/printing/token_print.c src/printing/parser_print.c src/free_memory/free_memory.c \
	$(PARSER_F) src/ft_error.c src/tests/parser_test.c \
	-Iincludes/ includes/parser.h includes/lexer.h includes/minishell.h \
	-Llibft -lft

test_builtin:
	@$(CC) $(CFLAGS) src/printing/token_print.c src/printing/parser_print.c src/free_memory/free_memory.c \
	$(BUILTIN_F) src/ft_error.c src/tests/builtin_test.c \
	-Iincludes/ includes/parser.h includes/lexer.h includes/minishell.h \
	-Llibft -lft -g

test_env:
	@$(CC) $(CFLAGS) src/printing/token_print.c src/printing/parser_print.c src/free_memory/free_memory.c \
	$(ENV_F) src/ft_error.c src/tests/env_test.c \
	-Iincludes/ includes/parser.h includes/lexer.h includes/minishell.h \
	-Llibft -lft -g
  
test_redir:
	$(CC) $(CFLAGS) src/printing/token_print.c src/printing/parser_print.c src/free_memory/free_memory.c \
	$(ENV_F) $(REDIR_F) $(BUILTIN_F) $(PARSER_F) src/ft_error.c src/tests/parser_test.c \
	-Iincludes/ includes/parser.h includes/lexer.h includes/minishell.h \
	-Llibft -lft -g

### LIBFT

libft: $(LIBFT)

$(LIBFT):
	@$(MAKE) -C libft
	@echo "$(COLOUR_GREEN) $(LIBFT) created$(COLOUR_END)"

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

re: fclean $(NAME) bonus

.PHONY: all clean fclean re bonus