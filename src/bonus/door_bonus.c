/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:39:10 by yoonslee          #+#    #+#             */
/*   Updated: 2023/11/02 10:35:44 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief When space key is pressed, check if
 * the position of player's 1.5 radius is door.
 * If if is, close the door and changes the character
 * to 'D'(Door) 
 * 
 * @return returns 1, if there was openable door.
 * 0, if there was no door
 */
int	check_closable(t_ray *ray)
{
	int	x;
	int	y;

	x = (int)ray->pix_x_pos / GRID_PIX;
	y = (int)ray->pix_y_pos / GRID_PIX;
	if (ray->data->map[y][x] == 'O')
		ray->data->map[y][x] = 'O';
	else if (ray->data->map[y][(int)(x - 1)] == 'O')
		ray->data->map[y][(int)(x - 1)] = 'D';
	else if (ray->data->map[y][(int)(x + 1)] == 'O')
		ray->data->map[y][(int)(x + 1)] = 'D';
	else if (ray->data->map[(int)(y - 1)][x] == 'O')
		ray->data->map[(int)(y - 1)][x] = 'D';
	else if (ray->data->map[(int)(y + 1)][x] == 'O')
		ray->data->map[(int)(y + 1)][x] = 'D';
	else
		return (0);
	return (1);
}

/**
 * @brief When return key is pressed, check if
 * the position of player's 1.5 radius is door.
 * If if is, opens the door and changes the character
 * to 'O'(Opened) 
 * 
 * @return returns 1, if there was openable door.
 * 0, if there was no door
 */
int	check_openable(t_ray *ray)
{
	int	x;
	int	y;

	x = (int)ray->pix_x_pos / GRID_PIX;
	y = (int)ray->pix_y_pos / GRID_PIX;
	if (ray->data->map[y][x] == 'D')
		ray->data->map[y][x] = 'O';
	else if (ray->data->map[y][(int)(x - 1)] == 'D')
		ray->data->map[y][(int)(x - 1)] = 'O';
	else if (ray->data->map[y][(int)(x + 1)] == 'D')
		ray->data->map[y][(int)(x + 1)] = 'O';
	else if (ray->data->map[(int)(y - 1)][x] == 'D')
		ray->data->map[(int)(y - 1)][x] = 'O';
	else if (ray->data->map[(int)(y + 1)][x] == 'D')
		ray->data->map[(int)(y + 1)][x] = 'O';
	else
		return (0);
	return (1);
}
