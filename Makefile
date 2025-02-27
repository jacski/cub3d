# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkalinow <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/10 11:19:28 by jkalinow          #+#    #+#              #
#    Updated: 2024/07/10 11:19:37 by jkalinow         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D
SRCS = $(wildcard srcs/*.c)
OBJS = $(SRCS:.c=.o)
MLX = minilibx-linux/libmlx.a
FLAGS = -Wall -Wextra -Werror
MINILIBX_PATH = ./minilibx-linux
INCLUDES = -I$(MINILIBX_PATH)
LIBS = -L$(MINILIBX_PATH) -lmlx -lX11 -lXext -lm

$(NAME): $(OBJS) $(MLX)
		cc $(FLAGS) -o $(NAME) $(OBJS) $(INCLUDES) $(LIBS)

%.o: %.c
		cc $(FLAGS) -c $< -o $@ $(INCLUDES)

all: $(NAME)

$(MLX):
	make -C minilibx-linux

clean:
		rm -f $(OBJS)
		make clean -C minilibx-linux

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
