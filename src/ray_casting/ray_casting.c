/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 07:25:36 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/16 13:44:49 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

void	texture_wall(t_ray *ray, int pos, int wall, float y_count)
{
	float			wall_start;
	float			wall_end;
	float			i;
	unsigned int	texture;

	i = 0;
	pos = WIN_SIZE_X - (pos + 1);
	// if (wall > WIN_SIZE_Y)
	// 	wall = WIN_SIZE_Y;
	wall_start = WIN_SIZE_Y / 2 - (wall / 2);
	wall_end = wall_start + wall;
	// if (wall_start < 0)
	// 	wall_start = 0;
	// if (wall_end > WIN_SIZE_Y)
	// 	wall_end = WIN_SIZE_Y;
	// printf("texture_wall : tex_x is %f, tex_y is %f, y_count is %f\n", ray->tex_x, ray->tex_y, y_count);
	// printf("wall start is %f, wall_end is %f\n", wall_start, wall_end);
	while ((int)(wall_start + i) < (int)wall_end)
	{
		// printf("tex_x is %f(%d), tex_y is %f(%d)\n", ray->tex_x, (int)ray->tex_x, ray->tex_y, (int)ray->tex_y);
		texture = my_mlx_pixel_get(ray->data->texture[set_wall_direction(ray)], \
		ray->tex_x, ray->tex_y);
		my_mlx_pixel_put(ray->cbd, pos, wall_start + i, texture);
		i++;
		ray->tex_y += y_count;
	}
}

// /**
//  * @brief
//  *
//  * @param ray
//  * @param ray_count (0 to 599)
//  */
// void	color_wall(t_ray *ray, int pos, int wall)
// {
// 	float		wall_start;
// 	float		wall_end;
// 	float		i;

// 	i = 0;
// 	pos = WIN_SIZE_X - (pos + 1);
// 	wall_start = WIN_SIZE_Y / 2 - (wall / 2);
// 	wall_end = wall_start + wall;
// 	if (wall_start < 0)
// 		wall_start = 0;
// 	if (wall_end > WIN_SIZE_Y)
// 		wall_end = WIN_SIZE_Y;
// 	while ((int)(wall_start + i) < (int)wall_end)
// 	{
// 		my_mlx_pixel_put(ray->cbd, pos, wall_start + i, GREY);
// 		i++;
// 	}
// }

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
	if (h_length != 0.0f && (h_length < v_length || v_length == 0.0f))
	{
		ray->shortest = 'h';
		ray->distance = h_length * cos(deg_to_rad(ray->ra - ray->pa));
	}
	else
	{
		ray->shortest = 'v';
		ray->distance = v_length * cos(deg_to_rad(ray->ra - ray->pa));
	}
	// printf("ray.ra is %f, ray pa is %f\n", ray->ra, ray->pa);
}
