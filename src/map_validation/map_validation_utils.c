/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:04:28 by yoonslee          #+#    #+#             */
/*   Updated: 2023/09/07 16:14:54 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map_validation.h"
#include "../../include/cub3d.h"

/**
 * @brief free mv_struct
 */
void	free_mv_struct(t_data *mv)
{
	if (mv->map)
		free_char_array(mv->map);
	if (mv->map_cpy)
		free_char_array(mv->map_cpy);
}

/*prints out error message accordingly and free the parsed contents
data struct should be added later.*/
void	print_error(t_cub *cub, t_data *mv, char *str, int code)
{
	ft_putstr_fd(str, 2);
	if (code == 1)
		free_struct(cub);
	if (code == 2)
	{
		free_struct(cub);
		free_mv_struct(mv);
	}
	exit(1);
}

/**
 * @brief copies the original map to map_cpy
 */
void	copy_map(t_cub *cub, t_data *mv)
{
	int	i;
	int	j;
	int	width;

	i = -1;
	j = 0;
	width = 0;
	mv->map_cpy = ft_calloc((mv->height + 1), sizeof(char *));
	if (!mv->map_cpy)
		print_error(cub, mv, "malloc_error\n", 2);
	while (++i < mv->height)
	{
		mv->map_cpy[i] = ft_strdup(mv->map[i]);
		if (!mv->map_cpy[i])
			print_error(cub, mv, "malloc_error\n", 2);
		if ((int)ft_strlen(mv->map_cpy[i]) > width)
			width = ft_strlen(mv->map_cpy[i]);
	}
	mv->width = width;
	// printf("width is %d\n", width);
	// print_map(mv->map_cpy);
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
		printf("%s\n", map[i]);
		i++;
	}
}

void	flood_fill(t_data *mv, int x, int y, char c)
{
	if (x < 0 || y < 0 || x > mv->height || y > mv->width || \
			mv->map_cpy[x][y] != c)
		return ;
	else if (x >= 0 && y >= 0 && x < mv->height && y < mv->width)
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
