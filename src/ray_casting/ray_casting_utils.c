/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 09:47:29 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/03 12:06:32 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

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
	// ray->vector->pa = deg_to_rad(ray->pa);
}
