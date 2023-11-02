/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:31:12 by yoonslee          #+#    #+#             */
/*   Updated: 2023/11/02 14:01:35 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/// @brief return the index of the last occurence if c in the string
/// @param str
/// @param c
/// @return -1 if can't find c
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

/// @brief searches for the player location and saves it in the struct
/// @param mv
void	player_location(t_data *mv)
{
	int	i;
	int	j;

	i = 0;
	while (i < mv->height)
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
}

/// @brief checks if character matches the one that should be in the map,
/// @param c character fromm the map string
/// @return if character is incorrect returns 0, if not, returns 1
int	map_character_check_b(char c)
{
	if (c != '1' && c != '0' && c != '\n' && c != 'N' && \
	c != 'S' && c != 'E' && c != 'W' && c != 32 && c != 'D'\
	&& c != 'C')
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
