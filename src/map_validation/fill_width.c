/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_width.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:05:53 by yoonslee          #+#    #+#             */
/*   Updated: 2023/10/17 12:25:45 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map_validation.h"

/// @brief fills temporary map, row by row so that all empty indexes that are
/// smaller than max width become X
/// @param mv
/// @param temp
/// @param i row number of map
/// @return filled row
static char	*fill_row(t_data *mv, char *temp, int i)
{
	int	j;

	j = 0;
	temp = ft_calloc(mv->width + 1, sizeof(char));
	while (mv->map_cpy[i][j])
	{
		temp[j] = mv->map_cpy[i][j];
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
			temp = fill_row(mv, temp, i);
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
		print_error(cub, mv, "map is null\n", 1);
	i = 0;
	while (cub->map_str[i])
	{
		if (cub->map_str[i] == '\n' && cub->map_str[i + 1] == '\n')
			print_error(cub, mv, "two consecutive new lines!\n", 1);
		i++;
	}
}
