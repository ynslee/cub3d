/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */ 
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:27:53 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/02 15:06:38 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

// static void	check_wall_hits(t_cbd *cbd, t_ray *ray, int dof)
// {
// 	if (dof == 10000)
// 		return ;
	
// }


// static void	horizontal_ray(t_cbd *cbd, t_ray *ray)
// {
// 	int			dof;

// 	dof = 0;
// 	ray->cotan = 1 / tan(deg_to_rad(ray->ra));
// 	if (sin(deg_to_rad(ray->ra)) > 0.001)
// 	{
// 		ray->ray_y = ((int)ray->vector->y / GRID_PIX) * GRID_PIX - 0.0001;
// 		ray->ray_x = (((int)ray->vector->y - ray->ray_y) * ray->cotan) + ray->vector->x;
// 		ray->yo = -GRID_PIX;
// 		ray->xo = -ray->yo * ray->cotan;
// 	}
// 	else if (sin(deg_to_rad(ray->ra)) < -0.001)
// 	{
// 		ray->ray_y = ((int)ray->vector->y / GRID_PIX) * GRID_PIX + GRID_PIX;
// 		ray->ray_x = (((int)ray->vector->y - ray->ray_y) * ray->cotan) + ray->vector->x;
// 		ray->yo = GRID_PIX;
// 		ray->xo = -ray->yo * ray->cotan;
// 	}
// 	else
// 	{
// 		ray->ray_x = ray->pix_x_pos;
// 		ray->ray_y = ray->pix_y_pos;
// 		dof = 10000;
// 	}
// 	check_wall_hits(cbd, ray, dof);
// }

// void	draw_rays(t_cbd *cbd, t_ray *ray)
// {
// 	ray->ra = fix_angle(ray->pa - FOV / 2);
// 	horizontal_ray(cbd, &ray);
// }
