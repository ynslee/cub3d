/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 07:25:36 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/04 11:08:59 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

void	cast_rays(t_ray *ray)
{
	printf("Coming to cast rays!\n");
	float	x;
	float	y;

	x = ray->pix_x_pos;
	y = ray->pix_y_pos;
	// ray->ra = fix_angle(ray->pa - FOV / 2);
	while (ray->ray_count < FOV)
	{
		ray->r_cos = cos(deg_to_rad(ray->ra));
		ray->r_sin = sin(deg_to_rad(ray->ra));
		x += ray->r_cos;
		y += ray->r_sin;
		if (ray->data->map[(int)y / GRID_PIX][(int)x / GRID_PIX] == '1')
		{
			ray->r_end_x = x;
			ray->r_end_y = y;
			bresenham(ray);
			ray->ray_count++;
			ray->ra += 1;
			cast_rays(ray);
			break;
		}
	}
}
