/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonseonlee <yoonseonlee@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 08:14:54 by yoonslee          #+#    #+#             */
/*   Updated: 2023/10/26 03:18:28 by yoonseonlee      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting_bonus.h"

int	mouse_event(int x, int y, t_ray *ray)
{
	if (ray->dragging)
	{
		if (x >= 0 && x < WIN_SIZE_X && y >= 0 && y < WIN_SIZE_Y)
		{
			ray->pa = fix_angle(ray->pa - ((int)ray->mou_x - x) * SENSITIVITY);
			ray->pdx = cos(deg_to_rad(ray->pa)) * PLAYER_S;
			ray->pdy = -sin(deg_to_rad(ray->pa)) * PLAYER_S;
		}
		ray->mou_x = x;
	}
	render_image_b(ray->cbd, ray);
	return (0);
}

int	mouse_press(int button, int x, int y, t_ray *ray)
{
	if (x >= 0 && x < WIN_SIZE_X && y >= 0 && y < WIN_SIZE_Y)
	{
		if (button == 1)
		{
			ray->dragging = 1;
			ray->mou_x = x;
		}
	}
	return (0);
}

int	mouse_release(int button, int x, int y, t_ray *ray)
{
	if (button == 1)
		ray->dragging = 0;
	if ((x < 0 || x >= WIN_SIZE_X) && (y < 0 || y >= WIN_SIZE_Y))
	{
		ray->dragging = 0;
	}
	return (0);
}
