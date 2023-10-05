/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 07:25:36 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/05 14:57:11 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

static void	calculate_distance(t_ray *ray)
{
	ray->distance = sqrt(pow(ray->r_end_x - ray->pix_x_pos, 2)
		+ pow(ray->r_end_y - ray->pix_y_pos, 2));
	// printf("ray->distance: %f\n", ray->distance);
	ray->wall_height = (WIN_SIZE_X / 2) / ray->distance;
	// printf("ray->wall_height: %f\n", ray->wall_height);
}

// static void	color_wall(t_ray *ray)
// {
// 	my_mlx_pixel_put(ray->cbd, )
// 	drawLine(rayCount, 0, rayCount, data.screen.halfHeight - wallHeight, "cyan");
// 	drawLine(rayCount, data.screen.halfHeight - wallHeight, rayCount, data.screen.halfHeight + wallHeight, "red");
// 	drawLine(rayCount, data.screen.halfHeight + wallHeight, rayCount, data.screen.height, "green");

// }
// WEST = BLACK
// EAST = WHITE
// SOUTH = GREY
// NORTH = GREEN

static int	set_wall_direction(t_ray *ray)
{
	if (ray->pa >= 0 && ray->pa < 90)
	{
		if (ray->ra >= 0 && ray->ra < 45)
			return (BLACK);
		if (ray->ra >=45 && ray->ra < 90)
			return (GREY);
	}
	if (ray->pa >= 90 && ray->pa < 180)
	{
		if (ray->ra >= 90 && ray->ra < 135)
			return (GREY);
		if (ray->ra >= 135 && ray->ra < 180)
			return (WHITE);
	}
	if (ray->pa >= 180 && ray->pa < 270)
	{
		if (ray->ra >= 180 && ray->ra < 225)
			return (WHITE);
		if (ray->ra >= 225 && ray->ra < 270)
			return (GREEN);
	}
	if (ray->pa >= 270 && ray->pa < 360)
	{
		if (ray->ra >= 270 && ray->ra < 315)
			return (GREEN);
		if (ray->ra >= 315 && ray->ra < 360)
			return (BLACK);
	}

}

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
