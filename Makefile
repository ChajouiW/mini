# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mochajou <mochajou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/30 10:15:34 by abahja            #+#    #+#              #
#    Updated: 2025/05/02 21:16:53 by mochajou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      = cc
CFLAGS  = -g #-fsanitize=address #-Werror -Wextra -Wall 
NAME    = minishell

SRC = minishell.c srcs/stdin_tostr.c token_gen/token_layer1.c ft_dllman.c syntax_layer.c listutils.c \
	  token_polisher.c expandator.c remove_space.c

OBJ     = $(SRC:.c=.o)

LIBS_DIR = libft
LIBFT_LINK = -L $(LIBS_DIR) -lft
LIBRL_LINK = -L $(LIBS_DIR) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LINK) $(LIBRL_LINK) -o $(NAME)
	@echo "minshell compiled successfully!"

.SECONDARY: $(OBJ)

clean:
	@rm -f $(OBJ)
	@echo "Cleaned object files!"

fclean: clean
	@rm -f $(NAME)
	@echo "Removed executable!"

re: fclean $(NAME)

.PHONY: all clean fclean re