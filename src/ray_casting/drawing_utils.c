/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 07:12:23 by yoonslee          #+#    #+#             */
/*   Updated: 2023/10/17 10:39:26 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"
#include "../../include/cub3d.h"

// "WEST" = BLACK
// "EAST" = WHITE
// "SOUTH" = GREY
// "NORTH" = GREEN

static int rays_looking_up(t_ray *ray)
{
	if ((int)ray->ra >= 0 && (int)ray->ra < 90)
	{
		if (ray->shortest == 'v') // v
			return (WE);
		if (ray->shortest == 'h') // h
			return (SO);
	}
	else if ((int)ray->ra >= 90 && (int)ray->ra < 180)
	{
		if (ray->shortest == 'v') // v
			return (EA);
		if (ray->shortest == 'h') // h
			return (SO);
	}
	return (-1);
}

static int rays_looking_down(t_ray *ray)
{
	if ((int)ray->ra >= 180 && (int)ray->ra < 270)
	{
		if (ray->shortest == 'v') // v
			return (EA);
		if (ray->shortest == 'h') // h
			return (NO);
	}
	else if ((int)ray->ra >= 270 && (int)ray->ra < 360)
	{
		if (ray->shortest == 'v') // v
			return (WE);
		if (ray->shortest == 'h') // h
			return (NO);
	}
	return (-1);
}
int	set_wall_direction(t_ray *ray)
{
	if ((int)ray->ra >= 0 && (int)ray->ra < 180)
		return (rays_looking_up(ray));
	else if ((int)ray->ra >= 180 && (int)ray->ra < 360)
		return (rays_looking_down(ray));
	return (-1);
}

/**
 * @brief finding the location of texture and draw the image
 * 
 * @param PR_PLANE Project plane :(WINDOW_WIDTH / 2) / tan(30degree)
 * @param y_count step size of traversing the image in y axis(top to bottom)
 */
void	draw_image(t_ray *ray, t_line *line)
{
	float	y_count;

	ray->wall_height = GRID_PIX / ray->distance * PR_PLANE;
	y_count = TEX_PIX / ray->wall_height;
	if (ray->shortest == 'h')
		texture_location(ray, y_count, line->x1, line->y1);
	else
		texture_location(ray, y_count, line->v_x1, line->v_y1);
	texture_wall(ray, ray->ray_count, (int)ray->wall_height, y_count);
}
