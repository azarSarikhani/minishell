# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 15:27:30 by djagusch          #+#    #+#              #
#    Updated: 2023/06/02 17:22:44 by djagusch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -I$I -std=c99 -O3 \
	-Wno-unused-result

NAME = libft.a

I := ../includes
HEADER = $I/libft.h

FILES = ft_atoi ft_bzero ft_calloc ft_isalnum \
	ft_isalpha ft_isascii ft_isdigit ft_isprint \
	ft_isspace ft_itoa ft_memchr ft_memcmp ft_memcpy \
	ft_memmove ft_memset ft_putchar_fd \
	ft_putendl_fd ft_putnbr_fd ft_putstr_fd \
	ft_split ft_strchr ft_strdup ft_striteri \
	ft_strjoin ft_strlcat ft_strlcpy ft_strlen \
	ft_strmapi ft_strncmp ft_strnstr ft_strrchr \
	ft_strtrim ft_substr ft_strcmp ft_tolower ft_toupper \
	ft_lstadd_back ft_lstadd_front ft_lstclear \
	ft_lstdelone ft_lstiter ft_lstlast ft_lstmap \
	ft_lstnew ft_lstsize ft_min ft_max ft_putchar \
	ft_putendl ft_putnbr ft_putstr ft_printf \
	ft_printf_char ft_printf_hex ft_printf_int ft_printf_pointer \
	ft_printf_string ft_printf_udec ft_printf_util \
	ft_printf_fd ft_printf_char_fd ft_printf_hex_fd ft_printf_int_fd \
	ft_printf_pointer_fd ft_printf_string_fd ft_printf_udec_fd \
	ft_printf_util_fd get_next_line ft_free ft_atof ft_atol ft_pow \
	ft_lenbase get_next_line ft_free_array ft_print_array \
	ft_count_elements ft_abs ft_bits ft_which_extr \
	ft_free_int_array ft_print_matrix
#	//add_to_array create_array destroy_array get_elem_array \
#	resize_array

S := srcs
SRCS := $(foreach FILE,$(FILES),$(shell find $S -type f -name $(FILE).c))

O := objs
OBJS := $(patsubst $S/%,$O/%,$(SRCS:.c=.o))
O_DIRS := $(dir $(OBJS))

all: $(NAME)

$(NAME): $(OBJS) $(SRCS)
	@ar rc $(NAME) $(OBJS)

$O/%.o: $S/%.c $(HEADER)| $O
	@$(CC) $(CFLAGS) -c $< -o $@

$O:
	@mkdir -p $(O_DIRS)

clean:
	@rm -f $(OBJS)
	@if [ -d $O ]; then $(RM) -rf $O $(O_DIRS); fi

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
