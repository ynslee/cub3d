/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 09:18:41 by yoonslee          #+#    #+#             */
/*   Updated: 2023/10/16 13:08:26 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/ray_casting.h"


/*calculates the texture x,y position for the vertical 
 * stripe of wall.
 * x is calculated by the direction of the ray and the position of the hit.*/
void	texture_location(t_ray *ray, float y_count, float x, float y)
{
	int	dir;

	ray->tex_y = 0;
	if (ray->wall_height > WIN_SIZE_Y)
		ray->tex_y = ((ray->wall_height - WIN_SIZE_Y) / 2) * y_count;
	dir = set_wall_direction(ray);
	// set_draw_texture(ray, dir);
	// printf("dir is %d, x is %f, y is %f\n", dir, x, y);
	if (dir == -1)
		ft_putstr_fd("Wall position can't be found\n", 2);
	if (dir == NO)
		ray->tex_x = TEX_PIX - 1 - ((int)x % TEX_PIX);
	else if (dir == WE)
		ray->tex_x = (int)y % TEX_PIX;
	else if (dir == SO)
		ray->tex_x = (int)x % TEX_PIX;
	else if (dir == EA)
		ray->tex_x = TEX_PIX - 1 - ((int)y % TEX_PIX);
	// printf("dir is %d, tex.x is %f, tex.y is %f\n", dir, ray->tex_x, ray->tex_y);
}
