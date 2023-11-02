/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 07:51:46 by jhusso            #+#    #+#             */
/*   Updated: 2023/11/02 14:09:07 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
- free map cpy and set to null
- make map cpy again
- set the buffer
- flood fill to check walls are closed
*/

static void	flood_fill_inside(t_cub *cub, t_data *mv, int x, int y)
{
	if (x < 0 || y < 0 || x > mv->height + 2 || y > mv->width + 2 \
		|| !mv->buffer_cpy[x][y])
		return ;
	if (mv->buffer_cpy[x][y] == 'X')
		print_error(cub, mv, "Wall not closed!\n", 1);
	if (mv->buffer_cpy[x][y] == ' ')
		print_error(cub, mv, "Map invalid!\n", 1);
	if (x >= 0 && y >= 0 && (mv->buffer_cpy[x][y] == '0' || \
	mv->buffer_cpy[x][y] == 'D' || mv->buffer_cpy[x][y] == 'C' \
	|| mv->buffer_cpy[x][y] == mv->player_view))
	{
		mv->buffer_cpy[x][y] = 'V';
		if (x < mv->height + 2)
			flood_fill_inside(cub, mv, x + 1, y);
		if (y < mv->width + 2)
			flood_fill_inside(cub, mv, x, y + 1);
		if (x > 0)
			flood_fill_inside(cub, mv, x - 1, y);
		if (y > 0)
			flood_fill_inside(cub, mv, x, y - 1);
	}
}

static void	ft_bx(char *s, size_t n)
{
	char	*ptr;
	size_t	i;

	ptr = (char *)s;
	i = 0;
	while (i < n)
		ptr[i++] = 'X';
}

void	set_buffer(t_cub *cub, t_data *data)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	data->buffer_cpy = ft_calloc(data->height + 3, sizeof(char *));
	while (++i < data->height + 2)
		data->buffer_cpy[i] = ft_calloc(data->width + 3, sizeof(char));
	ft_bx(data->buffer_cpy[0], data->width + 2);
	i = 1;
	j = 0;
	while (i < data->height + 1)
	{
		temp = ft_strjoin("X", data->map[j]);
		free(data->buffer_cpy[i]);
		data->buffer_cpy[i] = ft_strjoin(temp, "X");
		free(temp);
		temp = NULL;
		i++;
		j++;
	}
	ft_bx(data->buffer_cpy[i], data->width + 2);
	data->buffer_cpy[i + 1] = NULL;
	flood_fill_inside(cub, data, data->player_x + 1, data->player_y + 1);
}

int	wall_check(t_cub *cub, t_data *data)
{
	set_buffer(cub, data);
	return (0);
}
