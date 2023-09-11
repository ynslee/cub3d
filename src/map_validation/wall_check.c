/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 07:51:46 by jhusso            #+#    #+#             */
/*   Updated: 2023/09/11 12:44:00 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
- free map cpy and set to null
- make map cpy again
- set the buffer
- flood fill to check walls are closed

*/

void	flood_fill_inside(t_data *mv, char **map, int x, int y)
{
	if (x < 0 || y < 0 || x > mv->height - 1 || y > mv->width - 1 \
		|| !map[x][y])
		return ;
	if (map[x][y] == 'X')
		printf("Wall not closed!\n");
	if (x >= 0 && y >= 0 && map[x][y] != 'X')
	{
		if (map[x][y] == '0' || map[x][y] == mv->player_view || map[x][y] == ' ')
		{
			map[x][y] = 'V';
			if (x < mv->height - 1)
				flood_fill_inside(mv, map, x + 1, y);
			if (y < mv->width - 1)
				flood_fill_inside(mv, map, x, y + 1);
			if (x > 0)
				flood_fill_inside(mv, map, x - 1, y);
			if (y > 0)
				flood_fill_inside(mv, map, x, y - 1);
			print_map(map);
		}
	}
}

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
	flood_fill_inside(data, buffer_cpy, data->player_x, data->player_y);
	free_char_array(buffer_cpy);
}

int	wall_check(t_data *data)
{
	set_buffer(data);
	return (0);
}
