/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 07:12:23 by yoonslee          #+#    #+#             */
/*   Updated: 2023/10/16 10:17:33 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"
#include "../../include/cub3d.h"

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

/*
PR_PLANE is Project plane :(WINDOW_WIDTH / 2) / tan(30degree)
y_count is step size of traversing the image in y axis(top to bottom)*/
void	draw_image(t_ray *ray, t_line *line)
{
	float	y_count;

	ray->wall_height = GRID_PIX / ray->distance * PR_PLANE;
	y_count = TEX_PIX / ray->wall_height;
	if (ray->shortest == 'h')
	{
		printf("horizontal: ray.shortest is %c, x is %f, y is %f\n", ray->shortest, line->x1, line->y1);
		texture_location(ray, y_count, line->x1, line->y1);
	}
	else
	{
		printf("vertical: ray.shortest is %c, x is %f, y is %f\n", ray->shortest, line->v_x1, line->v_y1);
		texture_location(ray, y_count, line->v_x1, line->v_y1);
	}
	// color_wall(ray, ray->ray_count, (int)ray->wall_height);
	texture_wall(ray, ray->ray_count, (int)ray->wall_height, y_count);
}
