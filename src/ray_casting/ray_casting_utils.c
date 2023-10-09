/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 09:47:29 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/09 14:29:33 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

/*
Converts the (x, y) coordinates to respective grid coordinates while checking
coordinate for wall ('1')
*/

int	is_wall(t_ray *ray, float x, float y)
{
	// printf("line x1 value is %f\n", line.x1);
	// printf("line y1 value is %f\n", line.y1);
	// printf("x grid pos: %d\n", (int)(line.x1 / GRID_PIX));
	// printf("y grid pos: %d\n", (int)(line.y1 / GRID_PIX));
	if (((int)(ray->pix_x_pos / GRID_PIX) == (int)(x / GRID_PIX)) && ((int)(ray->pix_y_pos / GRID_PIX) == (int)(y / GRID_PIX)))
		return (0);
	// else if (ray->line->x1 <= 0 || ray->line->x1 < ray->data->width || ray->line->y1 <= 0 || ray->line->y1 < ray->data->height)
	// 	return (0);
	else if ((int)y / GRID_PIX >= 0 && (int)x / GRID_PIX >= 0 && (int)x / GRID_PIX < ray->data->width \
	&& (int)y / GRID_PIX < ray->data->height && \
	((ray->data->map[(int)(y / GRID_PIX - 0.01)][(int)x / GRID_PIX] == '1') || \
	(ray->data->map[(int)(y / GRID_PIX + 0.01)][(int)x / GRID_PIX] == '1') || \
	(ray->data->map[(int)y / GRID_PIX][(int)(x / GRID_PIX - 0.01)] == '1') || \
	(ray->data->map[(int)y / GRID_PIX][(int)(x / GRID_PIX + 0.01)] == '1')))
	{
		// printf("returning from is wall 1\n");
		return (1);
	}
	printf("returning from is wall 0\n");
	return(0);
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
