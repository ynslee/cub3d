/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:54:20 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/02 18:42:29 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

// static void	nose_diretion(t_line *line, t_ray *ray)
// {
// 	if (ray->data->player_view == 'E')
// 	{
// 		line->x1 = ray->pix_x_pos + ray->pdx * 5 + 10; //  317;
// 		line->y1 = ray->pix_y_pos + ray->pdy * 5; //  317;
// 	}
// 	if (ray->data->player_view == 'W')
// 	{

// 	}
// 	if (ray->data->player_view == 'N')
// 	{

// 	}
// 	if (ray->data->player_view == 'S')
// 	{

// 	}

// }

static void	nose_orientation(t_line *line, t_ray *ray)
{
	printf("line->x0: %i\tline->y0: %i\n", line->x0, line->y0);
	if (ray->pa == 90.0) // NORTH
	{
		line->x1 = line->x0;
		line->y1 = ray->pix_y_pos + ray->pdy * 5 - 40;
		printf("line->x1: %i\tline->y1: %i\n", line->x1, line->y1);
	}
	if (ray->pa == 270.0) // SOUTH
	{
		line->x1 = line->x0;
		line->y1 = ray->pix_y_pos + ray->pdy * 5 + 20;
		printf("line->x1: %i\tline->y1: %i\n", line->x1, line->y1);
	}
	if (ray->pa == 180.0) // WEST
	{
		line->x1 = ray->pix_x_pos + ray->pdx * 5 - 10;
		line->y1 = line->y0; //ray->pix_y_pos + ray->pdy * 5;
		printf("line->x1: %i\tline->y1: %i\n", line->x1, line->y1);
	}
	if (ray->pa == 0.0) // EAST
	{
		line->x1 = ray->pix_x_pos + ray->pdx * 5 + 10;
		line->y1 = line->y0;//ray->pix_y_pos + ray->pdy * 5;
		printf("line->x1: %i\tline->y1: %i\n", line->x1, line->y1);
	}
}

static void	init_line(t_line *line, t_ray *ray)
{
	line->x0 = ray->pix_x_pos;
	line->y0 = ray->pix_y_pos;
	nose_orientation(line, ray);
	printf("ray->pdx: %f\n", ray->pdx);
	printf("ray->pdy: %f\n", ray->pdy);
	// nose_direction(line, ray);
	// line->x1 = ray->pix_x_pos + ray->pdx * 5 + 10; //  317;
	// line->y1 = ray->pix_y_pos + ray->pdy * 5; //  317;
	// printf("line->x0 = %i\n", line->x0);
	// printf("line->y0 = %i\n", line->y0);
	// printf("line->x1 = %i\n", line->x1);
	// printf("line->y1 = %i\n", line->y1);

	line->dx = abs(line->x1 - line->x0);
	line->dy = -abs(line->y1 - line->y0);
	// printf("line->dx = %i\n", line->dx);
	// printf("line->dy = %i\n", line->dy);
	if (line->x1 > ray->pix_x_pos)
	{
		line->sx = 1;
		// printf("line->sx = %i\n", line->sx);
	}
	else
	{
		line->sx = -1;
	}
	if (line->y1 > ray->pix_y_pos)
	{
		line->sy = 1;
		// printf("line->sy = %i\n", line->sy);
	}
	else
	{
		line->sy = -1;
		// printf("line->sy = %i\n", line->sy);
	}
	line->error = line->dx + line->dy;
	line->error2 = line->error * 2;
}

void	bresenham(t_line *line, t_ray *ray)
{
	while (42)
	{
		my_mlx_pixel_put(ray->cbd, line->x0, line->y0, 0x00000000);
		if (line->x0 == line->x1 && line->y0 == line->y1)
			break ;
		if (line->error2 <= line->dx)
		{
			line->error += line->dx;
			line->y0 += line->sy;
		}
		if (line->error2 >= line->dy)
		{
			line->error += line->dy;
			line->x0 += line->sx;
		}
	}
}

void	draw_nose(t_ray *ray)
{
	t_line line;

	init_line(&line, ray);
	bresenham(&line, ray);
	// render_image(ray->cbd, ray, ray->data);
}
