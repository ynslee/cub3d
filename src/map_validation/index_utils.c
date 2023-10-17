/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:31:12 by yoonslee          #+#    #+#             */
/*   Updated: 2023/10/16 08:56:30 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map_validation.h"
#include "../../include/cub3d.h"

/**
 * @brief return the index of the last occurence if c in the string
 * returns -1 if can't find c
 */
int	ft_lastchr(char *str, char c)
{
	int	i;
	int	index;

	i = 0;
	index = -1;
	while (str[i])
	{
		if (str[i] == c)
			index = i;
		i++;
	}
	return (index);
}

void	player_location(t_data *mv)
{
	int	i;
	int	j;

	i = 0;
	while (i < mv->height) // while(mv->map[i])
	{
		j = 0;
		while (mv->map[i][j])
		{
			if (ft_strchr("NSEW", mv->map[i][j]))
			{
				mv->player_x = i;
				mv->player_y = j;
				mv->player_view = mv->map[i][j];
			}
			j++;
		}
		i++;
	}
	// printf("player position x: %d, y: %d\n", mv->player_x, mv->player_y);
}

/**
 * @brief if character doesn't matches the one that should be in the map,
 * returns 0. if not, returns 1
 */
int	map_character_check(char c)
{
	if (c != '1' && c != '0' && c != '\n' && c != 'N' && \
	c != 'S' && c != 'E' && c != 'W' && c != 32)
		return (0);
	return (1);
}

void	init_mv(t_data *mv)
{
	mv->height = 0;
	mv->width = 0;
	mv->map = NULL;
	mv->map_cpy = NULL;
	mv->buffer_cpy = NULL;
	mv->player_x = 0;
	mv->player_y = 0;
	mv->player_view = -1;
	mv->img_width = 64;
	mv->img_height = 64;
}
