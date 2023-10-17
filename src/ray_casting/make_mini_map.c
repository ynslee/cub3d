/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:19:46 by yoonslee          #+#    #+#             */
/*   Updated: 2023/10/17 13:24:27 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_casting.h"
#include "cub3d.h"

/**
 * @brief draw player on the minimap
 */
void	draw_player(t_cbd *cbd, t_ray *ray)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < 5)
	{
		y = 0;
		while (y < 5)
		{
			my_mlx_pixel_put(cbd, x + ((ray->pix_x_pos / 4) - 2), \
			y + ((ray->pix_y_pos / 4) - 2), PINK);
			y++;
		}
		x++;
	}
}

/**
 * @brief draw grid of the minimap so it is easier for the player to see
 *  the angle of the views
 */
static void	draw_grid(t_cbd *cbd, t_data *mv)
{
	int	x;
	int	y;

	x = 0;
	while (x < mv->width * MINI_PIX)
	{
		y = -1;
		while (++y < mv->height * MINI_PIX)
			my_mlx_pixel_put(cbd, x, y, BLACK);
		x = x + MINI_PIX;
	}
	x = -1;
	while (++x < mv->width * MINI_PIX)
	{
		y = 0;
		while (y < mv->height * MINI_PIX)
		{
			my_mlx_pixel_put(cbd, x, y, BLACK);
			y = y + MINI_PIX;
		}
	}
}

/**
 * @brief draw minimap's wall and path based on 
 */
static void	draw_map(t_cbd *cbd, int x, int y, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < MINI_PIX)
	{
		j = -1;
		while (++j < MINI_PIX)
		{
			my_mlx_pixel_put(cbd, x + i, y + j, color);
		}
	}
}

/**
 * @brief make minimap for the cub3D bonus part.
 * draws the preview of the map on the corner of the screen
 */
void	make_mini_map(t_cbd *cbd, t_data *mv)
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
			else if (mv->map[i][j] == '0')
				color = LIGHTBLUE;
			draw_map(cbd, j * MINI_PIX, i * MINI_PIX, color);
			j++;
		}
		i++;
	}
	draw_grid(cbd, mv);
}
