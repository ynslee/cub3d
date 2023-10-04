/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 07:25:36 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/04 12:30:22 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

void	cast_rays(t_ray *ray)
{
	float	x;
	float	y;

	x = ray->pix_x_pos;
	y = ray->pix_y_pos;
	// ray->ra = fix_angle(ray->pa - FOV / 2);
	while (ray->ray_count < FOV)
	{
		ray->pdx = cos(deg_to_rad(ray->ra));
		ray->pdy = -sin(deg_to_rad(ray->ra));
		x += ray->pdx;
		y += ray->pdy;
		if (ray->data->map[(int)y / GRID_PIX][(int)x / GRID_PIX] == '1')
		{
			ray->r_end_x = x;
			ray->r_end_y = y;
			bresenham(ray);
			ray->ray_count += 0.5;
			ray->ra = fix_angle(ray->ra + 0.5);
			cast_rays(ray);
			break;
		}
	}
}
