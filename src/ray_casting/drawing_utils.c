/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 07:12:23 by yoonslee          #+#    #+#             */
/*   Updated: 2023/10/12 12:43:20 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// unsigned int	ft_pixel_get()
//depth of view
//smoother line for the walls
// static void	calculate_distance(t_ray *ray)
// {
// 	ray->distance = sqrt(pow(ray->r_end_x - ray->pix_x_pos, 2)
// 		+ pow(ray->r_end_y - ray->pix_y_pos, 2));
// 	// printf("ray->distance: %f\n", ray->distance);
// 	ray->wall_height = ((WIN_SIZE_Y / 2) / ray->distance);
// 	printf("ray->wall_height: %f\n", ray->wall_height);
// }

// WEST = BLACK
// EAST = WHITE
// SOUTH = GREY
// NORTH = GREEN

static unsigned int	rays_looking_up(t_ray *ray)
{
	if ((int)ray->ra >= 0 && (int)ray->ra < 90)
	{
		if (ray->shortest == 'v') // v
			return (BLACK);
		if (ray->shortest == 'h') // h
			return (GREY);
	}
	else if ((int)ray->ra >= 90 && (int)ray->ra < 180)
	{
		if (ray->shortest == 'v') // v
			return (WHITE);
		if (ray->shortest == 'h') // h
			return (GREY);
	}
	return (0);
}

static unsigned int rays_looking_down(t_ray *ray)
{
	if ((int)ray->ra >= 180 && (int)ray->ra < 270)
	{
		if (ray->shortest == 'v') // v
			return (WHITE);
		if (ray->shortest == 'h') // h
			return (GREEN);
	}
	else if ((int)ray->ra >= 270 && (int)ray->ra < 360)
	{
		if (ray->shortest == 'v') // v
			return (BLACK);
		if (ray->shortest == 'h') // h
			return (GREEN);
	}
	return (0);
}
unsigned int	set_wall_direction(t_ray *ray)
{
	// printf("shortest: %i\n", ray->shortest);
	if ((int)ray->ra >= 0 && (int)ray->ra < 180)
		return (rays_looking_up(ray));
	else if ((int)ray->ra >= 180 && (int)ray->ra < 360)
		return (rays_looking_down(ray));
	return (0);
}

void	draw_image(t_cbd *cbd, t_ray *ray)
{
	ray->wall_height = WIN_SIZE_Y * 10 / ray->distance ;
	// printf("wall height is %f\n", ray->wall_height);
	color_wall(ray, ray->ray_count, ray->wall_height);
	(void)cbd;
	//render the walls
}