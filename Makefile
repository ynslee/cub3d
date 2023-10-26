# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoonseonlee <yoonseonlee@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/05 12:17:49 by yoonslee          #+#    #+#              #
#    Updated: 2023/10/26 03:13:43 by yoonseonlee      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COLOURS ###

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

### SET UP ###
CC = cc -arch x86_64
#MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit
CFLAGS =  -I$I -Wall -Wextra -Werror #-fsanitize=address,undefined #-g

RM = /bin/rm -f
RMDIR = /bin/rmdir -p

LIBFT = libft/libft.a

S = src
O = obj
I = include
B = obj_bonus

FILES = main\
		elements_to_struct\
		check_elements\
		file_validation_utils\
		read_file\
		map_check\
		map_validation_utils\
		index_utils\
		fill_width\
		wall_check\
		rgb_colour\
		drawing_utils\
		drawing\
		hooks\
		mlx_utils\
		movement\
		render\
		ray_casting_utils\
		ray_casting\
		texture\

B_FILES = main_bonus\
		elements_to_struct\
		check_elements\
		file_validation_utils\
		read_file\
		map_check_bonus\
		map_validation_utils\
		index_utils_bonus\
		fill_width\
		wall_check_bonus\
		rgb_colour_bonus\
		drawing_utils\
		drawing_bonus\
		mlx_utils\
		movement_bonus\
		ray_casting_utils_bonus\
		ray_casting\
		texture_bonus\
		hooks_bonus\
		make_mini_map_bonus\
		minimap_ray_bonus\
		mouse_hooks_bonus\
		render_bonus\
		door_bonus\

HEADER = cub3d.h libft.h file_validation.h map_validation.h ray_casting.h
HEADER := $(addprefix $I/,$(HEADER))

SRCS := $(foreach FILE,$(FILES),$(shell find $S -type f -name '$(FILE).c'))
OBJS = $(patsubst $S/%,$O/%,$(SRCS:.c=.o))
O_DIRS = $(dir $(OBJS))

B_HEADER = cub3d.h libft.h file_validation.h map_validation_bonus.h ray_casting_bonus.h
B_HEADER := $(addprefix $I/,$(B_HEADER))

B_SRCS := $(foreach B_FILE,$(B_FILES),$(shell find $S -type f -name '$(B_FILE).c'))
B_OBJS = $(patsubst $S/%,$B/%,$(B_SRCS:.c=.o))
B_O_DIRS = $(dir $(B_OBJS))

#Minilibx
MLX_PATH	= mlx/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)
MLX_LNK	= -L ./mlx -lmlx -framework OpenGL -framework AppKit

NAME = cub3D
NAME_BONUS = cub3D_bonus

### RULES ###
all: $(NAME)

$O/%.o: $S/%.c $(HEADER)
	@mkdir -p $(O_DIRS)
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	@echo "Compiling cub3D..."
	@$(CC) $(CFLAGS) $(MLX) $(MLX_LNK) $(LIBFT) $(OBJS) -o $(NAME)
	@echo "$(COLOUR_GREEN) $(NAME) created$(COLOUR_END)"

bonus: $(NAME_BONUS)

$B/%.o: $S/%.c $(B_HEADER)
	@mkdir -p $(B_O_DIRS)
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(NAME_BONUS): $(B_OBJS) $(MLX) $(LIBFT)
	@echo "Compiling cub3D_bonus..."
	@$(CC) $(CFLAGS) $(MLX) $(MLX_LNK) $(LIBFT) $(B_OBJS) -o $(NAME_BONUS)
	@echo "$(COLOUR_GREEN) $(NAME_BONUS) created$(COLOUR_END)"

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
	@if [ -d $O ]; then $(RM) -rf $(O_DIRS) $O; fi
	@if [ -d $B ]; then $(RM) -rf $(O_DIRS) $B; fi

fclean : clean
	@cd libft && $(MAKE) fclean
	@echo "$(COLOUR_RED) $(LIBFT) removed$(COLOUR_END)"
	@$(RM) $(NAME)
	@$(RM) $(NAME_BONUS)
	@echo "$(COLOUR_RED) $(NAME) or $(NAME_BONUS) removed$(COLOUR_END)"

re: fclean all

.PHONY: all clean fclean re
