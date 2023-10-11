/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 07:25:36 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/11 13:02:18 by yoonslee         ###   ########.fr       */
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

static unsigned int	rays_looking_up(t_ray *ray)
{
	if (ray->ra >= 0 && ray->ra < 90)
	{
		if (ray->shortest == 118) // v
			return (BLACK);
		if (ray->shortest == 104) // h
			return (GREY);
	}
	else if (ray->ra >= 90 && ray->ra < 180)
	{
		if (ray->shortest == 118) // v
			return (WHITE);
		if (ray->shortest == 104) // h
			return (GREY);
	}
	return (0);
}

static unsigned int rays_looking_down(t_ray *ray)
{
	if (ray->ra >= 180 && ray->ra < 270)
	{
		if (ray->shortest == 118) // v
			return (WHITE);
		if (ray->shortest == 104) // h
			return (GREEN);
	}
	else if (ray->ra >= 270 && ray->ra < 360)
	{
		if (ray->shortest == 118) // v
			return (BLACK);
		if (ray->shortest == 104) // h
			return (GREEN);
	}
	return (0);
}
unsigned int	set_wall_direction(t_ray *ray)
{
	// printf("shortest: %i\n", ray->shortest);
	if (ray->ra >= 0 && ray->ra < 180)
		return (rays_looking_up(ray));
	else if (ray->ra >= 180 && ray->ra < 360)
		return (rays_looking_down(ray));
	return (0);
}

/**
 * @brief
 *
 * @param ray
 * @param ray_count (0 to 599)
 */
static void	color_wall(t_ray *ray, int pos, int wall)
{
	float		wall_start;
	float		wall_end;
	float		i;

	i = 0;
	pos = WIN_SIZE_X - pos;
	wall_start = WIN_SIZE_Y / 2 - (wall / 2);
	wall_end = wall_start + wall;
	printf("wall start is %f\n", wall_start);
	printf("wall end is %f\n", wall_end);
	while (wall_start + i < wall_end)
	{
		my_mlx_pixel_put(ray->cbd, pos, wall_start + i, set_wall_direction(ray));
		i++;
	}
}

void	draw_image(t_cbd *cbd, t_ray *ray)
{
	ray->wall_height = WIN_SIZE_Y  * GRID_PIX / ray->distance ;
	printf("wall height is %f\n", ray->wall_height);
	color_wall(ray, ray->ray_count, ray->wall_height);
	(void)cbd;
	//render the walls
}

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

/**
 * @brief calculate and check the distance between horizontal and vertical length.
 * cosine function is to remove the fish-eye distortion.
 */
void	compare_draw_rays(t_ray *ray, t_line *line)
{
	float	h_length;
	float	v_length;

	h_length = sqrt(pow(line->x0 - line->x1, 2) + pow(line->y0 - line->y1, 2));
	v_length = sqrt(pow(line->x0 - line->v_x1, 2) + \
	pow(line->y0 - line->v_y1, 2));
	if (h_length != 0 && h_length < v_length)
	{
		ray->shortest = 'h';
		ray->distance = h_length * cos(deg_to_rad(ray->ra - ray->pa));
		line->x1 = (int)line->x1;
		line->y1 = (int)line->y1;
	}
	else if (v_length != 0)
	{
		ray->shortest = 'v';
		ray->distance = v_length * cos(deg_to_rad(ray->ra - ray->pa));
		line->x1 = (int)line->v_x1;
		line->y1 = (int)line->v_y1;
	}
	bresenham(ray, line, BLACK);
}
