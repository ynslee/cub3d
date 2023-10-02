/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:04:34 by yoonslee          #+#    #+#             */
/*   Updated: 2023/10/02 10:25:24 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map_validation.h"

int	fill_the_wall(t_cub *cub, t_data *mv)
{
	int		x;
	int		y;
	int		index;

	x = mv->player_x;
	y = 0;
	while (mv->map_cpy[x][y] == ' ')
		y++;
	if (mv->map_cpy[x][y] != '1')
		print_error(cub, mv, "map is not closed\n", 2);
	flood_fill(mv, x, y, mv->map_cpy[x][y]);
	x = 0;
	while (mv->map_cpy[x])
	{
		index = ft_lastchr(mv->map_cpy[x], 2 + '0');
		while (mv->map_cpy[x][index])
		{
			if (mv->map_cpy[x][index] == '1')
				return (1);
			index++;
		}
		x++;
	}
	return (0);
}

/**
 * @brief checks the height of the map and save it to struct.
 */
int	height_check(char *map, t_data *mv)
{
	int		i;
	int		height;
	int		width;

	i = 0;
	height = 1;
	width = 0;
	while (map[i])
	{
		if (map[i] == '\n')
			height++;
		i++;
	}
	mv->height = height;
	return (height);
}

/**
 * @brief Check if there is two maps.
 * if there is two maps, returns 1, if not returns 0
 */
int	two_maps_check(t_cub *cub, int height, t_data *mv)
{
	char	**temp;
	int		i;

	i = 0;
	if (cub->map_str == NULL)
		print_error(cub, mv, "map is null\n", 1);
	mv->map = ft_calloc((height + 1), sizeof(char *));
	if (!mv->map)
		print_error(cub, mv, "malloc_error\n", 1);
	temp = ft_split(cub->map_str, '\n');
	if (!temp)
		print_error(cub, mv, "split error\n", 1);
	while (temp[i])
	{
		mv->map[i] = ft_strdup(temp[i]);
		free(temp[i]);
		i++;
	}
	if (temp)
		free(temp);
	copy_map(cub, mv);
	fill_width(mv);
	if (fill_the_wall(cub, mv))
		return (1);
	return (0);
}

/**
 * @brief returns 0 if there is only one player.
 * returns 1 if there is no player or more than one player. *
 */
int	duplicate_player(char *map)
{
	int	i;
	int	player_flag;

	i = 0;
	player_flag = 0;
	while (map[i])
	{
		if (ft_strchr("NSEW", map[i]) && !player_flag)
			player_flag = 1;
		else if (ft_strchr("NSEW", map[i]) && player_flag)
			return (1);
		i++;
	}
	if (player_flag == 0)
		return (1);
	return (0);
}

/**
 * @brief Checks if there is two consecutive new lines in the map or more.
 * Checks if there is other character than 0,1,N,S,E,W
 * Check if there is multiple players
 * @return 1 if everything is valid, 0 if one of the condition is invalid.
 */
int	map_check(t_cub	*cub, t_data *mv)
{
	int		index;
	int		height;

	init_mv(mv);
	consecutive_new_lines(cub, mv);
	index = -1;
	while (cub->map_str[++index])
	{
		if (!map_character_check(cub->map_str[index]))
		{
			print_error(cub, mv, "map has invalid character!\n", 1);
			break ;
		}
	}
	if (duplicate_player(cub->map_str))
		print_error(cub, mv, "No player or more than one player!\n", 1);
	height = height_check(cub->map_str, mv);
	if (two_maps_check(cub, height, mv))
		print_error(cub, mv, "there are more than one map in the file!\n", 2);
	wall_check(cub, mv);
	return (0);
}
