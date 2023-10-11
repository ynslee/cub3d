/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   making_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:19:46 by yoonslee          #+#    #+#             */
/*   Updated: 2023/10/11 14:33:40 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_casting.h"
#include "cub3d.h"

void	draw_player(t_cbd *cbd, t_ray *ray)
{
	int	x = 0;
	int	y = 0;

	(void)cbd;
	while (x < 3)
	{
		y = 0;
		while (y < 3)
		{
			my_mlx_pixel_put(cbd, x + ray->pix_x_pos, y + ray->pix_y_pos, 0x00000000);
			y++;
		}
		x++;
	}
}

void	draw_grid(t_cbd *cbd, t_data *mv)
{
	int	x;
	int	y;

	x = 0;
	while (x < mv->width * GRID_PIX)
	{
		y = -1;
		while (++y < mv->height * GRID_PIX)
			my_mlx_pixel_put(cbd, x, y, BLACK);
		x = x + GRID_PIX;
	}
	x = -1;
	while (++x < mv->width * GRID_PIX)
	{
		y = 0;
		while (y < mv->height * GRID_PIX)
		{
			my_mlx_pixel_put(cbd, x, y, BLACK);
			y = y + GRID_PIX;
		}
	}
}

void	draw_map(t_cbd *cbd, int x, int y, int color)
{
	int	i;
	int	j;

	i = -1;
	// printf("in draw_map x: %i\ty: %i\n", x, y);
	while (++i < GRID_PIX)
	{
		j = -1;
		while (++j < GRID_PIX)
		{
			// printf("x:%i y:%i\n", i, j);
			my_mlx_pixel_put(cbd, x + i, y + j, color);
		}
	}

}

void	make_map(t_cbd *cbd, t_data *mv)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < mv->height)
	{
		j = 0;
		while (j < mv->width)
		{
			if (mv->map[i][j] == '1')
				color = BLUE;
			else
				color = LIGHTBLUE;
			draw_map(cbd, j * GRID_PIX, i * GRID_PIX, color);
			j++;
		}
		i++;
	}
	// draw_grid(cbd, mv);
}
