/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 07:51:46 by jhusso            #+#    #+#             */
/*   Updated: 2023/09/11 12:19:08 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
- free map cpy and set to null
- make map cpy again
- set the buffer
- flood fill to check walls are closed

*/

// void	flood_fill_inside(char **map, t_data *mv)
// {
// 	int	x;
// 	int	y;

// 	x = mv->player_x;
// 	y = mv->player_y;
// 	if (x < 0 || y < 0 || x > mv->height - 1 || y > mv->width - 1 \
// 		|| !mv->map_cpy[x][y])
// 		return ;
// 	else if (x >= 0 && y >= 0 && x < mv->height && y < mv->width \
// 	&& mv->map_cpy[x][y])
// 	{
// 		if (mv->map_cpy[x][y] == '0' || mv->map_cpy[x][y] == mv->player)
// 		{
// 			mv->map_cpy[x][y] = x;
// 			if (x < mv->height - 1)
// 				flood_fill(mv, x + 1, y, c);
// 			if (y < mv->width - 1)
// 				flood_fill(mv, x, y + 1, c);
// 			if (x > 0)
// 				flood_fill(mv, x - 1, y, c);
// 			if (y > 0)
// 				flood_fill(mv, x, y - 1, c);
// 		}
// 	}
// }

static void	ft_bx(void *s, size_t n)
{
	char	*ptr;
	size_t	i;

	ptr = (char *)s;
	i = 0;
	while (i < n)
		ptr[i++] = 'X';
}

void	set_buffer(t_data *data)
{
	char	**buffer_cpy;
	int		i;
	int		j;

	i = -1;
	buffer_cpy = ft_calloc(data->height + 3, sizeof(char *));
	while (++i < data->height + 2)
		buffer_cpy[i] = ft_calloc(data->width + 3, sizeof(char *));
	ft_bx(buffer_cpy[0], data->width + 2);
	i = 1;
	j = 0;
	while (i < data->height + 1)
	{
		buffer_cpy[i] = ft_strjoin("X", data->map[j]);
		buffer_cpy[i] = ft_strjoin(buffer_cpy[i], "X");
		i++;
		j++;
	}
	printf("%i\n", i);
	ft_bx(buffer_cpy[i], data->width + 2);
	print_map(buffer_cpy);
	free_char_array(buffer_cpy);
	flood_fill_inside(buffer_cpy, data);
}

int	wall_check(t_data *data)
{
	set_buffer(data);
	return (0);
}
