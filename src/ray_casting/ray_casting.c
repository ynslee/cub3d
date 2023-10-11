/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 07:25:36 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/11 12:48:08 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

//depth of view
//smoother line for the walls
// static void	calculate_distance(t_ray *ray)
// {
// 	ray->distance = sqrt(pow(ray->r_end_x - ray->pix_x_pos, 2)
// 		+ pow(ray->r_end_y - ray->pix_y_pos, 2));
// 	// printf("ray->distance: %f\n", ray->distance);
// 	ray->wall_height = ((WIN_SIZE_Y / 2) / ray->distance);
// 	printf("ray->wall_height: %f\n", ray->wall_height);
// }

// WEST = BLACK
// EAST = WHITE
// SOUTH = GREY
// NORTH = GREEN

static unsigned int	rays_looking_up(int shortest)
{
	if (shortest >= 0 && shortest < 90)
	{
		if (shortest == 118) // v
			return (BLACK);
		if (shortest == 104) // h
			return (GREY);
	}
	if (shortest >= 90 && shortest < 180)
	{
		if (shortest == 118) // v
			return (WHITE);
		if (shortest == 104) // h
			return (GREY);
	}
	return (0);
}

static unsigned int rays_loking_down(int shortest)
{
	if (shortest >= 180 && shortest < 270)
	{
		if (shortest == 118) // v
			return (WHITE);
		if (shortest == 104) // h
			return (GREEN);
	}
	if (shortest >= 270 && shortest < 360)
	{
		if (shortest == 118) // v
			return (BLACK);
		if (shortest == 104) // h
			return (GREEN);
	}
}
unsigned int	set_wall_direction(t_ray *ray)
{
	// printf("shortest: %i\n", ray->shortest);
	if (ray->ra >= 0 && ray->ra < 180)
		return (rays_looking_up(ray->shortest));
	if (ray->ra >= 180 && ray->ra < 360)
		return (rays_looking_down(ray->shortest));
	return (0);
}

/**
 * @brief
 *
 * @param ray
 * @param ray_count (0 to 599)
 */
// static void	color_wall(t_ray *ray, int pos, int wall)
// {
// 	float		wall_start;
// 	float		wall_end;
// 	float		i;

// 	i = 0;
// 	pos = WIN_SIZE_X - pos;
// 	wall_start = WIN_SIZE_Y / 2 - (wall);
// 	wall_end = WIN_SIZE_Y / 2 + (wall);
// 	printf("wall start is %f\n", wall_start);
// 	printf("wall end is %f\n", wall_end);
// 	while (wall_start + i < wall_end)
// 	{
// 		my_mlx_pixel_put(ray->cbd, pos, wall_start + i, BLACK);
// 		i++;
// 	}
// }

// void	draw_ray(t_ray *ray)
// {
// 	bresenham(ray, BLACK);
// 	calculate_distance(ray);
// 	color_wall(ray, ray->ray_count, ray->wall_height);
// 	//render the walls
// }

// void	cast_rays(t_ray *ray)
// {
// 	float	x;
// 	float	y;

// 	x = ray->pix_x_pos;
// 	y = ray->pix_y_pos;
// 	ray->ray_count = 0;
// 	while (ray->ray_count < WIN_SIZE_X)
// 	{
// 		ray->pdx = cos(deg_to_rad(ray->ra)) * 0.2;
// 		ray->pdy = -sin(deg_to_rad(ray->ra)) * 0.2;
// 		x += ray->pdx;
// 		y += ray->pdy;
// 		if (ray->data->map[(int)y / GRID_PIX][(int)x / GRID_PIX] == '1' \
// 		|| is_wall(ray, x, y))
// 		{
// 			ray->r_end_x = floor(x);
// 			ray->r_end_y = floor(y);
// 			draw_ray(ray);
// 			// bresenham(ray);
// 			ray->ray_count += 1;
// 			ray->ray_count += 1;
// 			ray->ra = fix_angle(ray->ra + (float)FOV / WIN_SIZE_X);
// 			// printf("fov / win_size = %f\n", (float)FOV / WIN_SIZE_X);
// 			// printf("fixed RA: %f!\n", ray->ra);
// 			x = ray->pix_x_pos;
// 			y = ray->pix_y_pos;
// 			// break ;
// 		}
// 	}
// }
