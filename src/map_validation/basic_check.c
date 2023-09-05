/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:04:34 by yoonslee          #+#    #+#             */
/*   Updated: 2023/09/05 17:25:25 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// First check of the map
//  Is there a player? or multiple players (also if map only ones, it would be caught here)
//  is there invalid character
//  more than 2 consecutive '\n'
// If there is two different maps?
//  Changing the wall element with floodfill algo -> if there is two maps, invalid -> if player is inside wall, invalid?

#include "../../include/map_validation.h"

// char	**copy_map(char *map)
// {
// 	char	*temp;
// 	char	**out;

// 	temp = ft_calloc(ft_strlen(map) + 1, sizeof(char));
// 	temp = ft_strdup(map);
// 	out = ft_split(map, '\n');
// 	return(out);
// }

int	height_check(char *map)
{
	// int		i;
	// int		height;

	
}

int	two_maps_check(char *map, int height)
{
	char	**map_cpy;
	int		i;

	if (map == NULL)
		print_error("map is null");
	map_cpy = (char **)malloc(height * sizeof(char *));
	split_result = ft_split(map_line, '\n');
	while (split_result[i])
	{
		sl->map[i] = ft_strdup(split_result[i]);
		free(split_result[i]);
		split_result[i] = NULL;
		i++;
	}
	free(split_result);
	validate_map_rectangular(sl);
	validate_map_char(sl);
	validate_map_walls(sl);
	copy_map(sl);
	if (sl->h <= 2 || sl->w <= 2)
		print_error(6, sl);
	validate_map_path(sl, sl ->p_x, sl ->p_y);
	if (sl->map_validity != 1)
		print_error(6, sl);
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
int	map_check(char *map)
{
	int		index;
	char	**map_cpy;
	int		height;

	index = ft_strchr_index(map, '\n');
	if (map[index + 1] == '\n')
		print_error("two consecutive new lines!");
	index = 0;
	while (map[index])
	{
		if (map[index] != '1' && map[index] != '0' && map[index] != '\n' && \
		map[index] != 'N' && map[index] != 'S' && map[index] != 'E' && \
		map[index] != 'W')
			print_error("map has invalid character!");
		index++;
	}
	if (duplicate_player(map))
		print_error("There are more than one player!");
	printf("there has been no errors! yay!\n");
	height = height_check(map);
	two_maps_check(map, height);
	return (0);
}
