/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:04:34 by yoonslee          #+#    #+#             */
/*   Updated: 2023/09/07 09:11:19 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// First check of the map
//  Is there a player? or multiple players (also if map only ones, it would be caught here)
//  is there invalid character
//  more than 2 consecutive '\n'
// If there is two different maps?
//  Changing the wall element with floodfill algo -> if there is two maps, invalid -> if player is inside wall, invalid?

#include "../../include/map_validation.h"

int	fill_the_wall(t_data *mv)
{
	int		x;
	int		y;
	int		index;

	x = mv->player_x;
	y = 0;
	while (mv->map_cpy[x][y] == ' ')
		y++;
	flood_fill(mv, x, y, mv->map_cpy[x][y]);
	print_map(mv->map_cpy);
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

	i = 0;
	height = 1;
	while (map[i])
	{
		if (map[i] == '\n')
			height++;
		i++;
	}
	mv->height = height;
	printf("height is %d\n", height);
	return (height);
}

/**
 * @brief Check if there is two maps.
 * if there is two maps, returns 1, if not returns 0
 */
int	two_maps_check(char *map, int height, t_data *mv)
{
	char	**temp;
	int		i;

	i = 0;
	if (map == NULL)
		print_error("map is null");
	mv->map = ft_calloc((height + 1), sizeof(char *));
	if (!mv->map)
		print_error("malloc_error");
	temp = ft_split(map, '\n');
	while (temp[i])
	{
		mv->map[i] = ft_strdup(temp[i]);
		free(temp[i]);
		temp[i] = NULL;
		i++;
	}
	free(temp);
	copy_map(mv);
	if (fill_the_wall(mv))
		return (1);
	return (0);
}

/**
 * @brief returns 0 if there is only one player.
 * returns 1 if there is more than one player. * 
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
	return (0);
}

/**
 * @brief Checks if there is two consecutive new lines in the map or more.
 * Checks if there is other character than 0,1,N,S,E,W
 * Check if there is multiple players
 * @return 1 if everything is valid, 0 if one of the condition is invalid.
 */
int	map_check(char *map, t_data *mv)
{
	int		index;
	int		height;

	index = ft_strchr_index(map, '\n');
	if (map[index + 1] == '\n')
		print_error("two consecutive new lines!");
	index = 0;
	while (map[index])
	{
		if (map[index] != '1' && map[index] != '0' && map[index] != '\n' && \
		map[index] != 'N' && map[index] != 'S' && map[index] != 'E' && \
		map[index] != 'W' && map[index] != 32)
		{
			print_error("map has invalid character!");
			break ;
		}
		index++;
	}
	if (duplicate_player(map))
		print_error("There are more than one player!");
	printf("there has been no errors! yay!\n");
	height = height_check(map, mv);
	if (two_maps_check(map, height, mv))
		print_error("there are more than one map in the file!");
	return (0);
}
