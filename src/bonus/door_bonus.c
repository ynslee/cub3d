/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:39:10 by yoonslee          #+#    #+#             */
/*   Updated: 2023/10/25 16:05:01 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting_bonus.h"
#include "../../include/cub3d.h"

int	check_closable(t_ray *ray)
{
	int	x;
	int	y;

	x = (int)ray->pix_x_pos / GRID_PIX;
	y = (int)ray->pix_y_pos / GRID_PIX;
	if (ray->data->map[y][x] == 'O')
		ray->data->map[y][x] = 'D';
	else if (ray->data->map[y][x - 1] == 'O')
		ray->data->map[y][x - 1] = 'D';
	else if (ray->data->map[y][x + 1] == 'O')
		ray->data->map[y][x + 1] = 'D';
	else if (ray->data->map[y - 1][x] == 'O')
		ray->data->map[y - 1][x] = 'D';
	else if (ray->data->map[y + 1][x] == 'O')
		ray->data->map[y + 1][x] = 'D';
	else
		return (0);
	return (1);
}


int	check_openable(t_ray *ray)
{
	int	x;
	int	y;

	x = (int)ray->pix_x_pos / GRID_PIX;
	y = (int)ray->pix_y_pos / GRID_PIX;
	if (ray->data->map[y][x] == 'D')
		ray->data->map[y][x] = 'O';
	else if (ray->data->map[y][x - 1] == 'D')
		ray->data->map[y][x - 1] = 'O';
	else if (ray->data->map[y][x + 1] == 'D')
		ray->data->map[y][x + 1] = 'O';
	else if (ray->data->map[y - 1][x] == 'D')
		ray->data->map[y - 1][x] = 'O';
	else if (ray->data->map[y + 1][x] == 'D')
		ray->data->map[y + 1][x] = 'O';
	else
		return (0);
	return (1);
}
