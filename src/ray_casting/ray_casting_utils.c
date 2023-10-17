/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 09:47:29 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/17 12:32:34 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

int	is_wall(t_ray *ray, float x, float y)
{
	// if (((int)(ray->pix_x_pos / GRID_PIX) == (int)(x / GRID_PIX)) && \
	// ((int)(ray->pix_y_pos / GRID_PIX) == (int)(y / GRID_PIX)))
	// 	return (0);
	if (ray->data->map[(int)y / GRID_PIX][(int)x / GRID_PIX] == '1')
		return (1);
	return (0);
}

float	fix_angle(float a)
{
	if (a < 0)
		a += 360;
	if (a > 359)
		a -= 360;
	return (a);
}

float	deg_to_rad(float degree)
{
	float	radians;

	radians = degree * (M_PI / 180.0);
	return (radians);
}

void	player_orientation_to_angle(t_data *mv, t_ray *ray)
{
	if (mv->player_view == 'N')
		ray->pa = 90.0;
	if (mv->player_view == 'S')
		ray->pa = 270.0;
	if (mv->player_view == 'W')
		ray->pa = 180.0;
	if (mv->player_view == 'E')
		ray->pa = 0.0;
	ray->pdx = cos(deg_to_rad(ray->pa)) * 20;
	ray->pdy = -sin(deg_to_rad(ray->pa)) * 20;
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
