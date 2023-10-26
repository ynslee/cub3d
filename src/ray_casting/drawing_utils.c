/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonseonlee <yoonseonlee@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 07:12:23 by yoonslee          #+#    #+#             */
/*   Updated: 2023/10/26 02:14:56 by yoonseonlee      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"
#include "../../include/cub3d.h"

static int	rays_looking_up(t_ray *ray)
{
	if ((int)ray->ra >= 0 && (int)ray->ra < 90)
	{
		if (ray->shortest == 'v')
			return (WE);
		if (ray->shortest == 'h')
			return (SO);
	}
	else if ((int)ray->ra >= 90 && (int)ray->ra < 180)
	{
		if (ray->shortest == 'v')
			return (EA);
		if (ray->shortest == 'h')
			return (SO);
	}
	return (-1);
}

static int	rays_looking_down(t_ray *ray)
{
	if ((int)ray->ra >= 180 && (int)ray->ra < 270)
	{
		if (ray->shortest == 'v')
			return (EA);
		if (ray->shortest == 'h')
			return (NO);
	}
	else if ((int)ray->ra >= 270 && (int)ray->ra < 360)
	{
		if (ray->shortest == 'v')
			return (WE);
		if (ray->shortest == 'h')
			return (NO);
	}
	return (-1);
}

/**
 * @brief Set the wall direction based on the ray's horizontal
 * and vertical hit and the ray angle.
 * 
 * @return side of the wall that the ray hits
 */
int	set_wall_direction(t_ray *ray)
{
	if ((int)ray->ra >= 0 && (int)ray->ra < 180)
		return (rays_looking_up(ray));
	else if ((int)ray->ra >= 180 && (int)ray->ra < 360)
		return (rays_looking_down(ray));
	return (-1);
}
