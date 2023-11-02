/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 09:18:41 by yoonslee          #+#    #+#             */
/*   Updated: 2023/11/02 10:03:35 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief based on the x,y position of wall & its texture position,
 * we paint the wall of the maps with xpm images
 * 
 * @param wall height of the wall
 * @param w_pos wall_position : North, West, South, East and Door
 * @param y_count how fast we need to chage the position of the y of texture.
 */
void	texture_wall_b(t_ray *ray, int pos, int wall, int door)
{
	int				wall_start;
	int				w_pos;
	int				i;
	unsigned int	texture;

	i = 0;
	w_pos = 0;
	pos = WIN_SIZE_X - (pos + 1);
	wall_start = WIN_SIZE_Y / 2 - (wall / 2);
	if (door)
		w_pos = DOOR;
	else
		w_pos = set_wall_direction(ray);
	while (wall_start + i < wall_start + wall)
	{
		texture = my_mlx_pixel_get(ray->data->textures[w_pos], \
		(int)ray->tex_x, (int)ray->tex_y);
		my_mlx_pixel_put(ray->cbd, pos, wall_start + i, texture);
		i++;
		ray->tex_y += ray->y_count;
	}
}

/**
 * @brief calculating texture's x by checking the  direction of hitthing the wall
 * (horizontal or vertical) and it's x y position. y will start from 0 unless
 * it's size is bigger than height of the wall.
 * 
 * commented out functions work?? My calculation works?? confused? by. Sunny
 */
void	texture_location(t_ray *ray, float y_count, float x, float y)
{
	int	dir;

	ray->tex_y = 0;
	if (ray->wall_height > WIN_SIZE_Y)
		ray->tex_y = ((ray->wall_height - WIN_SIZE_Y) / GRID_PIX) * y_count;
	dir = set_wall_direction(ray);
	if (dir == -1)
		ft_putstr_fd("Wall position can't be found\n", 2);
	if (dir == NO)
		ray->tex_x = ((int)(x - 1) % TEX_PIX);
	else if (dir == WE)
		ray->tex_x = (int)y % TEX_PIX;
	else if (dir == SO)
		ray->tex_x = (int)x % TEX_PIX;
	else if (dir == EA)
		ray->tex_x = TEX_PIX - 1 - ((int)y % TEX_PIX);
}
