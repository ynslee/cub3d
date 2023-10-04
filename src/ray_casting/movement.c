/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:19:57 by yoonslee          #+#    #+#             */
/*   Updated: 2023/10/04 10:20:02 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

int	side_wall_check2(t_ray *ray, t_vector *next, float degree)
{
	if (degree >= (float)180 && degree < (float)270)
	{
		if (!ray->data->map[(int)next->y][(int)next->x + 1] || \
		!ray->data->map[(int)next->y - 1][(int)next->x])
			return (0);
		if (ray->data->map[(int)next->y][(int)next->x + 1] == '1' && \
		ray->data->map[(int)next->y - 1][(int)next->x] == '1')
			return (0);
	}
	if (degree >= (float)270 && degree < (float)360)
	{
		if (!ray->data->map[(int)next->y][(int)next->x - 1] || \
		!ray->data->map[(int)next->y - 1][(int)next->x])
			return (0);
		if (ray->data->map[(int)next->y][(int)next->x - 1] == '1' && \
		ray->data->map[(int)next->y - 1][(int)next->x] == '1')
			return (0);
	}
	return (1);
}

/**
 * @brief checks to see if player can move between the wall.
 * Based on the degree(angle), we manually check if there is wall diagonally.
 * @param next player's next x, y position
 * @param degree player angle
 * @return returns 1 if there is no side_wall, returns 0 if there is side_walls.
 */
int	side_wall_check(t_ray *ray, t_vector *next, float degree)
{
	if (degree >= (float)0 && degree < (float)90)
	{
		if (!ray->data->map[(int)next->y][(int)next->x - 1] || \
		!ray->data->map[(int)next->y + 1][(int)next->x])
			return (0);
		if (ray->data->map[(int)next->y][(int)next->x - 1] == '1' && \
		ray->data->map[(int)next->y + 1][(int)next->x] == '1')
			return (0);
	}
	if (degree >= (float)90 && degree < (float)180)
	{
		if (!ray->data->map[(int)next->y][(int)next->x + 1] || \
		!ray->data->map[(int)next->y + 1][(int)next->x])
			return (0);
		if (ray->data->map[(int)next->y][(int)next->x + 1] == '1' && \
		ray->data->map[(int)next->y + 1][(int)next->x] == '1')
			return (0);
	}
	else if ((degree >= (float)180 && degree < (float)360))
		return (side_wall_check2(ray, next, degree));
	return (1);
}

/**
 * @brief check if next movement is movable
 * 
 * @param x next x position
 * @param y next y position
 * @return returns 1 if movable, if not, returns 0
 */
int	movable(float x, float y, t_ray *ray)
{
	t_vector	next;
	t_vector	current;

	current.x = ray->pix_x_pos / GRID_PIX;
	current.y = ray->pix_y_pos / GRID_PIX;
	next.x = x / GRID_PIX;
	next.y = y / GRID_PIX;
	printf("current.x is %d(%f)\n", (int)current.x, current.x);
	printf("current.y is %d(%f)\n", (int)current.y, current.y);
	printf("next.x is %d(%f)\n", (int)next.x, next.x);
	printf("next.y is %d(%f)\n", (int)next.y, next.y);
	if (ray->data->map[(int)next.y][(int)next.x] && \
	ray->data->map[(int)next.y][(int)next.x] == '1')
		return (0);
	if (((int)current.y == (int)next.y) && (int)current.x == (int)next.x)
		return (1);
	else
		return (side_wall_check(ray, &next, fix_angle(ray->pa)));
	return (1);
}

void	move_sideway(t_ray *ray, char *direction)
{
	double	angle;
	float	x;
	float	y;

	if (ft_strncmp_all(direction, "left"))
		angle = fix_angle(ray->pa - 90);
	else
		angle = fix_angle(ray->pa + 90);
	x = ray->pix_x_pos + (cos(deg_to_rad(angle)) * PLAYER_S);
	y = ray->pix_y_pos + (-sin(deg_to_rad(angle)) * PLAYER_S);
	if (movable(x, y, ray))
	{
		ray->pix_x_pos = x;
		ray->pix_y_pos = y;
	}
}

/**
 * @brief move forward and backwards as a player.
 *  pdx is divided by PLAYER_S so we slow down the player's movement. 
 * @param ray 
 * @param direction 
 */
void	move_frontback(t_ray *ray, char *direction)
{
	float	x;
	float	y;

	if (ft_strncmp_all(direction, "up"))
	{
		x = ray->pix_x_pos - ray->pdx / PLAYER_S;
		y = ray->pix_y_pos - ray->pdy / PLAYER_S;
	}
	else
	{
		x = ray->pix_x_pos + ray->pdx / PLAYER_S;
		y = ray->pix_y_pos + ray->pdy / PLAYER_S;
	}
	if (movable(x, y, ray))
	{
		ray->pix_x_pos = x;
		ray->pix_y_pos = y;
	}
}
