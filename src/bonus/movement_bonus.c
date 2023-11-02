/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:19:57 by yoonslee          #+#    #+#             */
/*   Updated: 2023/11/02 14:33:52 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	side_wall_check2(t_ray *ray, t_vector *next, float degree)
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
static int	side_wall_check(t_ray *ray, t_vector *next, float degree)
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
	if (ray->data->map[(int)next.y][(int)next.x] && \
	(ray->data->map[(int)(next.y + 0.1)][(int)next.x] == '1' || \
	ray->data->map[(int)(next.y - 0.1)][(int)next.x] == '1' || \
	ray->data->map[(int)next.y][(int)(next.x + 0.1)] == '1' || \
	ray->data->map[(int)next.y][(int)(next.x - 0.1)] == '1'))
		return (0);
	if (ray->data->map[(int)next.y][(int)next.x] && \
	(ray->data->map[(int)(next.y + 0.1)][(int)next.x] == 'D' || \
	ray->data->map[(int)(next.y - 0.1)][(int)next.x] == 'D' || \
	ray->data->map[(int)next.y][(int)(next.x + 0.1)] == 'D' || \
	ray->data->map[(int)next.y][(int)(next.x - 0.1)] == 'D'))
		return (0);
	else if (((int)current.y / GRID_PIX == (int)next.y / GRID_PIX) && \
	(int)current.x / GRID_PIX == (int)next.x / GRID_PIX)
		return (1);
	else
		return (side_wall_check(ray, &next, fix_angle(ray->pa)));
	return (1);
}

/**
 * @brief moves the player left and right
 */
void	move_sideway_b(t_ray *ray, char *direction)
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
		if (ray->data->map[(int)ray->pix_y_pos / GRID_PIX][(int)ray->pix_x_pos / GRID_PIX] == 'C')
			ray->data->map[(int)ray->pix_y_pos / GRID_PIX][(int)ray->pix_x_pos / GRID_PIX] = '0';
		ray->pix_x_pos = x;
		ray->pix_y_pos = y;
	}
}

/**
 * @brief move forward and backwards as a player.
 */
void	move_frontback_b(t_ray *ray, char *direction)
{
	float	x;
	float	y;

	if (ft_strncmp_all(direction, "up"))
	{
		x = ray->pix_x_pos - ray->pdx;
		y = ray->pix_y_pos - ray->pdy;
	}
	else
	{
		x = ray->pix_x_pos + ray->pdx;
		y = ray->pix_y_pos + ray->pdy;
	}
	if (movable(x, y, ray))
	{
		if (ray->data->map[(int)ray->pix_y_pos / GRID_PIX][(int)ray->pix_x_pos / GRID_PIX] == 'C')
			ray->data->map[(int)ray->pix_y_pos / GRID_PIX][(int)ray->pix_x_pos / GRID_PIX] = '0';
		ray->pix_x_pos = x;
		ray->pix_y_pos = y;
	}
}
