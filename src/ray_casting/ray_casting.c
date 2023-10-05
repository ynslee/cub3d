/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 07:25:36 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/05 14:48:52 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

static void	calculate_distance(t_ray *ray)
{
	ray->distance = sqrt(pow(ray->r_end_x - ray->pix_x_pos, 2)
		+ pow(ray->r_end_y - ray->pix_y_pos, 2));
	// printf("ray->distance: %f\n", ray->distance);
	ray->wall_height = round((WIN_SIZE_Y / 2) / ray->distance);
	printf("ray->wall_height: %d\n", ray->wall_height);
}

/**
 * @brief 
 * 
 * @param ray 
 * @param ray_count (0 to 599)
 */
static void	color_wall(t_ray *ray, int pos, int wall)
{
	int		wall_start;
	int		wall_end;
	int		i;

	i = 0;
	pos = WIN_SIZE_X - pos;
	wall_start = WIN_SIZE_Y / 2 - (wall);
	wall_end = WIN_SIZE_Y / 2 + (wall);
	printf("wall start is %d\n", wall_start);
	printf("wall end is %d\n", wall_end);
	while (wall_start + i < wall_end)
	{
		my_mlx_pixel_put(ray->cbd, pos, wall_start + i, BLACK);
		i++;
	}
}

void	draw_ray(t_ray *ray)
{
	bresenham(ray, BLACK);
	calculate_distance(ray);
	color_wall(ray, ray->ray_count, ray->wall_height);
	//render the walls
}

void	cast_rays(t_ray *ray)
{
	float	x;
	float	y;

	x = ray->pix_x_pos;
	y = ray->pix_y_pos;
	 ray->ray_count = 0;
	while (ray->ray_count < WIN_SIZE_X)
	{
		ray->pdx = cos(deg_to_rad(ray->ra)) * 0.2;
		ray->pdy = -sin(deg_to_rad(ray->ra)) * 0.2;
		x += ray->pdx;
		y += ray->pdy;
		if (ray->data->map[(int)y / GRID_PIX][(int)x / GRID_PIX] == '1' \
		|| is_wall(ray, x, y))
		{
			ray->r_end_x = floor(x);
			ray->r_end_y = floor(y);
			draw_ray(ray);
			// bresenham(ray);
			ray->ray_count += 1;
			ray->ra = fix_angle(ray->ra + (float)FOV / WIN_SIZE_X);
			// printf("fov / win_size = %f\n", (float)FOV / WIN_SIZE_X);
			// printf("fixed RA: %f!\n", ray->ra);
			x = ray->pix_x_pos;
			y = ray->pix_y_pos;
			// break ;
		}
	}
}
