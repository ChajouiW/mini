# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abahja <abahja@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/03 13:00:24 by abahja            #+#    #+#              #
#    Updated: 2025/04/26 16:53:01 by abahja           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS := ft_atoi.c    ft_isalpha.c ft_memchr.c  ft_memset.c  ft_strlcat.c ft_strnstr.c	\
		ft_bzero.c   ft_isascii.c ft_memcmp.c  ft_strchr.c  ft_strlcpy.c ft_strrchr.c	\
		ft_calloc.c  ft_isdigit.c ft_memcpy.c  ft_strdup.c  ft_strlen.c  ft_substr.c	\
		ft_isalnum.c ft_isprint.c ft_memmove.c ft_strncmp.c ft_tolower.c ft_toupper.c	\
		ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c		\
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strcmp.c ft_isspace.c \
		ft_malloc.c

SRCSB := ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c  \
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS := $(SRCS:.c=.o)

OBJSB := $(SRCSB:.c=.o)

CFLAGS := -Wall -Wextra -Werror

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)
	@echo "$"                                                                                         \033[1;36m------matnsach dir clean by abahja{h3nix}------\n$(RESET)"

bonus: $(OBJSB)
	ar -crs $(NAME) $^

$(NAME): $(OBJS)
	ar -crs $@ $^

%.o: %.c
	@echo "||$(RED)tiki taka-->>$(GREEN)" $< "<--\033[1;36mbroski wait$(BLUE)|| \n |> ------cmd-------->"
	cc $(CFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)                                                                                             <-Safi b7->\n$(RESET)"
	rm -f $(OBJSB) $(OBJS)


fclean: clean
	rm -f $(NAME)

re: fclean all re