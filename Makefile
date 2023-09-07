# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/05 12:17:49 by yoonslee          #+#    #+#              #
#    Updated: 2023/09/07 10:31:53 by yoonslee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COLOURS ###

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

### SET UP ###
CC = cc
CFLAGS =  -I$I -Wall -Wextra -Werror

RM = /bin/rm -f
RMDIR = /bin/rmdir -p

LIBFT = libft/libft.a

S = src
O = obj
I = include

FILES = main\
		check_textures\
		basic_check\
		map_validation_utils\
		index_utils\

HEADER = cub3d.h libft.h file_validation.h
HEADER := $(addprefix $I/,$(HEADER))

SRCS := $(foreach FILE,$(FILES),$(shell find $S -type f -name '$(FILE).c'))
OBJS = $(patsubst $S/%,$O/%,$(SRCS:.c=.o))
O_DIRS = $(dir $(OBJS))

#Minilibx
MLX_PATH	= mlx/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)
MLX_LNK	= -L ./mlx -lmlx -framework OpenGL -framework AppKit

NAME = cub3D

### RULES ###
all: $(MLX) $(LIBFT) $(NAME)

$O/%.o: $S/%.c $(HEADER)
	@mkdir -p $(O_DIRS)
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(NAME): $(OBJS)
	@echo "Compiling cub3D..."
	@$(CC) $(CFLAGS) $(MLX) $(MLX_LNK) $(LIBFT) $(OBJS) -o $(NAME)
	@echo "$(COLOUR_GREEN) $(NAME) created$(COLOUR_END)"

### MLX
$(MLX):
	@echo "Making MiniLibX..."
	@make -sC $(MLX_PATH)
	@echo "$(COLOUR_GREEN) $(MLX) created$(COLOUR_END)"

### LIBFT

libft: $(LIBFT)

$(LIBFT):
	@echo "Making libft..."
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
	@echo "$(COLOUR_RED) $(LIBFT) removed$(COLOUR_END)"
	@$(RM) $(NAME)
	@echo "$(COLOUR_RED) $(NAME) removed$(COLOUR_END)"

re: fclean all

.PHONY: all clean fclean re
