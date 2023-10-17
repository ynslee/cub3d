/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:04:28 by yoonslee          #+#    #+#             */
/*   Updated: 2023/10/17 12:23:58 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map_validation.h"
#include "../../include/cub3d.h"

/**
 * @brief free mv_struct
 */
void	free_mv_struct(t_data *mv)
{
	int	i;
	if (mv->map)
		free_char_array(mv->map);
	if (mv->map_cpy)
		free_char_array(mv->map_cpy);
	if (mv->buffer_cpy)
		free_char_array(mv->buffer_cpy);
	i = 0;
	while (i < 4)
	{
		if (mv->texture[i])
		{
			free (mv->texture[i]);
			mv->texture[i] = NULL;
		}
		i++;
	}
}


/// @brief print the error message, frees struct if its already allocated and
/// exits
/// @param cub
/// @param mv
/// @param str error message
/// @param code flag if struct needs to be freed
void	print_error(t_cub *cub, t_data *mv, char *str, int code)
{
	ft_putstr_fd(str, 2);
	if (code == 1)
		free_cub_struct(cub);
	if (code == 2)
	{
		free_cub_struct(cub);
		free_mv_struct(mv);
	}
	exit(1);
}
/// @brief makes a copy of mv->map and finds the width of the map
/// @param cub
/// @param mv
void	copy_map(t_cub *cub, t_data *mv)
{
	int	i;
	int	width;

	i = 0;
	width = 0;
	mv->map_cpy = ft_calloc((mv->height + 1), sizeof(char *));
	if (!mv->map_cpy)
		print_error(cub, mv, "malloc_error\n", 2);
	while (i < mv->height && mv->map[i])
	{
		mv->map_cpy[i] = ft_strdup(mv->map[i]);
		if (!mv->map_cpy[i])
			print_error(cub, mv, "malloc_error\n", 2);
		if ((int)ft_strlen(mv->map_cpy[i]) > width)
			width = ft_strlen(mv->map_cpy[i]);
		i++;
	}
	mv->width = width;
	player_location(mv);
}

/**
 * @brief print the map that is 2Darray
 */
void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("row index = %i\t%s\n", i, map[i]);
		i++;
	}
	printf("\n");
}

/// @brief flood fills the walls, searching recursively 1's
/// @param mv
/// @param x row -index
/// @param y char in row -index
/// @param c character in the map (1)
void	flood_fill(t_data *mv, int x, int y, char c)
{
	if (x < 0 || y < 0 || x >= mv->height || y >= mv->width || \
			mv->map_cpy[x][y] != c || !mv->map_cpy[x][y])
		return ;
	else if (x >= 0 && y >= 0 && x < mv->height && \
	y < mv->width && mv->map_cpy[x][y])
	{
		if (mv->map_cpy[x][y] == c)
		{
			mv->map_cpy[x][y] = c + 1;
			if (x < mv->height - 1)
				flood_fill(mv, x + 1, y, c);
			if (y < mv->width - 1)
				flood_fill(mv, x, y + 1, c);
			if (x > 0)
				flood_fill(mv, x - 1, y, c);
			if (y > 0)
				flood_fill(mv, x, y - 1, c);
		}
	}
}
