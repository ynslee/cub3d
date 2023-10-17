/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 07:25:36 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/17 10:08:53 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

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
	if (((int)(ray->pix_x_pos / MINI_PIX) == (int)(x / MINI_PIX)) && ((int)(ray->pix_y_pos / MINI_PIX) == (int)(y / MINI_PIX)))
		return (0);
	if ((ray->data->map[(int)(y / MINI_PIX - 0.01)][(int)x / MINI_PIX] == '1') || \
		(ray->data->map[(int)(y / MINI_PIX + 0.01)][(int)x / MINI_PIX] == '1') || \
		(ray->data->map[(int)y / MINI_PIX][(int)(x / MINI_PIX - 0.01)] == '1') || \
		(ray->data->map[(int)y / MINI_PIX][(int)(x / MINI_PIX + 0.01)] == '1'))
		return (1);
	return(0);
}

void	cast_rays(t_ray *ray)
{
	float	x;
	float	y;

	x = ray->pix_x_pos / 4;
	y = ray->pix_y_pos / 4;
	ray->ray_count = 0;
	while (ray->ray_count < (ray->data->width * MINI_PIX))
	{
		ray->pdx = cos(deg_to_rad(ray->ra)) * 0.2;
		ray->pdy = -sin(deg_to_rad(ray->ra)) * 0.2;
		x += ray->pdx;
		y += ray->pdy;
		if (ray->data->map[(int)y / MINI_PIX][(int)x / MINI_PIX] == '1' \
		|| bh_hit_wall(ray, x, y))
		{
			ray->r_end_x = floor(x);
			ray->r_end_y = floor(y);
			bresenham(ray, ray->line, BLACK);
			ray->ray_count += 1;
			ray->ra = fix_angle(ray->ra + (float)FOV / (ray->data->width * MINI_PIX));
			x = ray->pix_x_pos / 4;
			y = ray->pix_y_pos / 4;
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

	h_length = sqrt(pow((line->x0 - line->x1), 2) + \
	pow((line->y0 - line->y1), 2));
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
}
