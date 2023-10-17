/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_width.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:05:53 by yoonslee          #+#    #+#             */
/*   Updated: 2023/10/17 15:22:55 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map_validation.h"
#include "../../include/cub3d.h"

char	*fill_temp(t_data *mv, char **map, char *temp, int i)
{
	int	j;

	j = 0;
	temp = ft_calloc(mv->width + 1, sizeof(char));
	while (map[i][j])
	{
		temp[j] = map[i][j];
		j++;
	}
	while (j < mv->width)
	{
		temp[j] = 'X';
		j++;
	}
	temp[j] = '\0';
	return (temp);
}

void	fill_width(t_data *mv)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (mv->map_cpy[i])
	{
		if ((int)ft_strlen(mv->map_cpy[i]) < mv->width)
		{
			temp = fill_temp(mv, mv->map_cpy, temp, i);
			free(mv->map_cpy[i]);
			mv->map_cpy[i] = ft_strdup(temp);
			free(temp);
		}
		i++;
	}
}

void	consecutive_new_lines(t_cub *cub, t_data *mv)
{
	int	i;

	i = 0;
	while (cub->map_str[i])
	{
		if (cub->map_str[i] == '\n' && cub->map_str[i + 1] == '\n')
			print_error(cub, mv, "two consecutive new lines!\n", 1);
		i++;
	}
}
