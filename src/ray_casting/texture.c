/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 09:18:41 by yoonslee          #+#    #+#             */
/*   Updated: 2023/10/17 10:57:03 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/ray_casting.h"

/**
 * @brief based on the x,y position of wall & its texture position,
 * we paint the wall of the maps with xpm images
 * 
 * @param wall height of the wall
 * @param y_count how fast we need to chage the position of the y of texture.
 */
void	texture_wall(t_ray *ray, int pos, int wall, float y_count)
{
	int				wall_start;
	int				wall_end;
	int				i;
	unsigned int	texture;

	i = 0;
	pos = WIN_SIZE_X - (pos + 1);
	wall_start = WIN_SIZE_Y / 2 - (wall / 2);
	wall_end = wall_start + wall;
	while (wall_start + i < wall_end)
	{
		texture = my_mlx_pixel_get(ray->data->texture[set_wall_direction(ray)], \
		(int)ray->tex_x, (int)ray->tex_y);
		my_mlx_pixel_put(ray->cbd, pos, wall_start + i, texture);
		i++;
		ray->tex_y += y_count;
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
	// if (dir == NO)
	// 	ray->tex_x = TEX_PIX - 1 - ((int)x % TEX_PIX);
	if (dir == NO)
		ray->tex_x = ((int)(x - 1) % TEX_PIX);
	else if (dir == WE)
		ray->tex_x = (int)y % TEX_PIX;
	else if (dir == SO)
		ray->tex_x = (int)x % TEX_PIX;
	else if (dir == EA)
		ray->tex_x = TEX_PIX - 1 - ((int)y % TEX_PIX);
	// else if (dir == EA)
	// 	ray->tex_x = ((int)(y - 1) % TEX_PIX);
}
