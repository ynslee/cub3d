/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 07:25:36 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/05 09:41:52 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

static void	calculate_distance(t_ray *ray)
{
	ray->distance = sqrt(pow(ray->r_end_x - ray->pix_x_pos, 2)
		+ pow(ray->r_end_y - ray->pix_y_pos, 2));
	printf("ray->distance: %f\n", ray->distance);
	ray->wall_height = (WIN_SIZE_X / 2) / ray->distance;
	printf("ray->wall_height: %f\n", ray->wall_height);
}

// static void	color_wall(t_ray *ray);
// {

// }

void	draw_ray(t_ray *ray)
{
	bresenham(ray, BLACK);
	calculate_distance(ray);
	// color_wall(ray);
	//render the walls
}

void	cast_rays(t_ray *ray)
{
	float	x;
	float	y;

	x = ray->pix_x_pos;
	y = ray->pix_y_pos;
	while (ray->ray_count < FOV)
	{
		ray->pdx = cos(deg_to_rad(ray->ra));
		ray->pdy = -sin(deg_to_rad(ray->ra));
		x += ray->pdx;
		y += ray->pdy;
		if (ray->data->map[(int)y / GRID_PIX][(int)x / GRID_PIX] == '1' \
		|| is_wall(ray, x, y))
		{
			ray->r_end_x = x;
			ray->r_end_y = y;
			draw_ray(ray);
			// bresenham(ray);
			ray->ray_count += 0.1;
			ray->ra = fix_angle(ray->ra + 0.1);
			x = ray->pix_x_pos;
			y = ray->pix_y_pos;
			// break ;
		}
	}
}
