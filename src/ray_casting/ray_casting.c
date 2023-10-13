/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 07:25:36 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/13 09:15:31 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

/**
 * @brief
 *
 * @param ray
 * @param ray_count (0 to 599)
 */
void	color_wall(t_ray *ray, int pos, int wall)
{
	float		wall_start;
	float		wall_end;
	float		i;

	i = 0;
	pos = WIN_SIZE_X - (pos + 1);
	wall_start = WIN_SIZE_Y / 2 - (wall / 2);
	wall_end = wall_start + wall;
	if (wall_start < 0)
		wall_start = 0;
	if (wall_end > WIN_SIZE_Y)
		wall_end = WIN_SIZE_Y;
	while ((int)(wall_start + i) < (int)wall_end)
	{
		my_mlx_pixel_put(ray->cbd, pos, wall_start + i, set_wall_direction(ray));
		i++;
	}
}

static int	bh_hit_wall(t_ray *ray, float x, float y)
{
	if (((int)(ray->pix_x_pos / GRID_PIX) == (int)(x / GRID_PIX)) && ((int)(ray->pix_y_pos / GRID_PIX) == (int)(y / GRID_PIX)))
		return (0);
	if ((ray->data->map[(int)(y / GRID_PIX - 0.01)][(int)x / GRID_PIX] == '1') || \
		(ray->data->map[(int)(y / GRID_PIX + 0.01)][(int)x / GRID_PIX] == '1') || \
		(ray->data->map[(int)y / GRID_PIX][(int)(x / GRID_PIX - 0.01)] == '1') || \
		(ray->data->map[(int)y / GRID_PIX][(int)(x / GRID_PIX + 0.01)] == '1'))
		return (1);
	return(0);
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
		|| bh_hit_wall(ray, x, y))
		{
			ray->r_end_x = floor(x);
			ray->r_end_y = floor(y);
			bresenham(ray, ray->line, BLACK);
			ray->ray_count += 1;
			ray->ra = fix_angle(ray->ra + (float)FOV / WIN_SIZE_X);
			x = ray->pix_x_pos;
			y = ray->pix_y_pos;
		}
	}
}

/**
 * @brief calculate and check the distance between horizontal and vertical length.
 * cosine function is to remove the fish-eye distortion.
 */
void	compare_draw_rays(t_ray *ray, t_line *line)
{
	float	h_length;
	float	v_length;

	h_length = sqrt(pow((line->x0 - line->x1), 2) + pow((line->y0 - line->y1), 2));
	v_length = sqrt(pow((line->x0 - line->v_x1), 2) + \
	pow((line->y0 - line->v_y1), 2));
	// printf("h calculation is %f and %f\n", line->x0 - line->x1, line->y0 - line->y1);
	// printf("v calculation is %f and %f\n", line->x0 - line->v_x1, line->y0 - line->v_y1);
	// printf("ray angle is %f\n", ray->ra);
	// printf("h_length is %f\n", h_length);
	// printf("v_length is %f\n", v_length);
	if (h_length != 0 && h_length < v_length)
	{
		ray->shortest = 'h';
		ray->distance = h_length * cos(deg_to_rad(ray->ra - ray->pa));
		line->x1 = (int)line->x1;
		line->y1 = (int)line->y1;
	}
	else if (v_length != 0 && v_length < h_length)
	{
		ray->shortest = 'v';
		ray->distance = v_length * cos(deg_to_rad(ray->ra - ray->pa));
		line->x1 = (int)line->v_x1;
		line->y1 = (int)line->v_y1;
	}
}
