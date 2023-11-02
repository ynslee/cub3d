/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 09:47:29 by jhusso            #+#    #+#             */
/*   Updated: 2023/11/02 14:28:06 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/ray_casting_bonus.h"

/**
 * @brief check if there is wall in the next position with dda algorithm
 *
 * @param x next position of x
 * @param y next position of y
 * @return 1 if there is wall, 0 if there isn't any wall
 */
int	is_wall_b(t_ray *ray, float x, float y)
{
	if (((int)(ray->pix_x_pos / GRID_PIX) == (int)(x / GRID_PIX)) && \
	((int)(ray->pix_y_pos / GRID_PIX) == (int)(y / GRID_PIX)))
		return (0);
	if (ray->data->map[(int)y / GRID_PIX][(int)x / GRID_PIX] == '1' || \
	ray->data->map[(int)y / GRID_PIX][(int)x / GRID_PIX] == 'D' || \
	ray->data->map[(int)y / GRID_PIX][(int)x / GRID_PIX] == 'C')
		return (1);
	return (0);
}

/**
 * @brief fix angle to be in between 0-359
 * 
 * @return fixed angle after calculation of +- 360 based on the condition
 */
float	fix_angle(float a)
{
	if (a < 0)
		a += 360;
	if (a > 359)
		a -= 360;
	return (a);
}

/**
 * @brief change the degree to radian for the usage in mathmatical functions
 * 
 * @return radian value of the angle
 */
float	deg_to_rad(float degree)
{
	float	radians;

	radians = degree * (M_PI / 180.0);
	return (radians);
}

/**
 * @brief Based on the player's character on the map, assign the player angle
 * and calculate pdx and pdy
 */
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
 * @brief calculate and check the distance between horizontal and 
 * vertical length. cosine function is to remove the fish-eye distortion.
 * @return returns 1 if the hit is door, if not, it returns 0.
 */
int	compare_draw_rays_b(t_ray *ray, t_line *line, int door)
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
		if ((int)(line->y1 / GRID_PIX) < ray->data->height && 
		(int)(line->x1 / GRID_PIX) < ray->data->width && \
		ray->data->map[(int)(line->y1 / GRID_PIX)]
		[(int)(line->x1 / GRID_PIX)] == 'D')
			door = 1;
		if ((int)(line->y1 / GRID_PIX) < ray->data->height && 
		(int)(line->x1 / GRID_PIX) < ray->data->width && \
		ray->data->map[(int)(line->y1 / GRID_PIX)]
		[(int)(line->x1 / GRID_PIX)] == 'C')
			door = 2;
	}
	else
	{
		ray->shortest = 'v';
		ray->distance = v_length * cos(deg_to_rad(ray->ra - ray->pa));
		if ((int)(line->v_y1 / GRID_PIX) < ray->data->height && 
		(int)(line->v_x1 / GRID_PIX) < ray->data->width && \
		ray->data->map[(int)(line->v_y1 / GRID_PIX)]
		[(int)(line->v_x1 / GRID_PIX)] == 'D')
			door = 1;
		if ((int)(line->v_y1 / GRID_PIX) < ray->data->height && 
		(int)(line->v_x1 / GRID_PIX) < ray->data->width && \
		ray->data->map[(int)(line->v_y1 / GRID_PIX)]
		[(int)(line->v_x1 / GRID_PIX)] == 'C')
			door = 2;
	}
	return (door);
}
