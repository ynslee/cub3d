# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/05 12:17:49 by yoonslee          #+#    #+#              #
#    Updated: 2023/09/05 13:05:55 by jhusso           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
SRCS = src/main.c src/file_validation/check_textures.c
OBJS = $(patsubst $S/%,$O/%,$(SRCS:.c=.o))
CC = cc
HEADER = include/cub3d.h
FLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit

all:$(NAME)

$(NAME):$(OBJS)
	make -C libft all
	$(CC) $(FLAGS) $(OBJS) -I$(HEADER) ./libft/libft.a $(MLX_FLAGS) -o $(NAME)

$(OBJS):$(SRCS)
	$(CC) -c $(FLAGS) $(SRCS) -I$(HEADER)

clean:
		rm -rf $(OBJS)
		make -C libft clean

fclean:clean
		rm -rf $(NAME)
		rm -rf libft/libft.a

re: fclean clean all

.PHONY: all clean fclean re
