/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_width.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:05:53 by yoonslee          #+#    #+#             */
/*   Updated: 2023/10/17 15:31:03 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map_validation.h"

/// @brief fills temporary map, row by row so that all empty indexes that are
/// smaller than max width become X
/// @param mv
/// @param temp
/// @param i row number of map
/// @return filled row
char	*fill_row(t_data *mv, char **map, char *temp, int i)
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

/// @brief loops trough map_cpy row by row, and send rows to be filled in
/// fill_row
/// @param mv
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
			temp = fill_row(mv, mv->map_cpy, temp, i);
			free(mv->map_cpy[i]);
			mv->map_cpy[i] = ft_strdup(temp);
			free(temp);
		}
		i++;
	}
}
/// @brief Checks that map_stris not null and then for two consecutive new lines
/// @param cub
/// @param mv
void	consecutive_new_lines(t_cub *cub, t_data *mv)
{
	int	i;

	if (cub->map_str == NULL)
		print_error(cub, mv, "Map is null\n", 1);
	i = 0;
	while (cub->map_str[i])
	{
		if (cub->map_str[i] == '\n' && cub->map_str[i + 1] == '\n')
			print_error(cub, mv, "Two consecutive new lines!\n", 1);
		i++;
	}
}
