/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 07:25:36 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/04 09:39:53 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

void	cast_rays(t_ray *ray)
{
	float	x;
	float	y;

	x = ray->pix_x_pos;
	y = ray->pix_y_pos;
	// printf("BEFORE INCREMENT:\nx: %f\ty: %f\n", x, y);
	while (ray->ray_count < FOV)
	{
		ray->r_cos = cos(deg_to_rad(ray->ra));
		ray->r_sin = sin(deg_to_rad(ray->ra));
		// printf("ray->cos: %f\tray->sin: %f\n", ray->r_cos, ray->r_sin);
		if (ray->data->map[(int)y / GRID_PIX][(int)x / GRID_PIX] == '1')
		{
			// printf("Found wall!\n");
			ray->r_end_x = x;
			ray->r_end_y = y;
			bresenham(ray);
			ray->ray_count++;
			ray->ra += 1;
			// printf("NEW ray->ra: %f\n", ray->ra);
			cast_rays(ray);
			break;
		}
		// printf("AFTER INCREMENT:\nx: %f\ty: %f\n", x, y);
		x += ray->r_cos;
		y += ray->r_sin;
	}
}
