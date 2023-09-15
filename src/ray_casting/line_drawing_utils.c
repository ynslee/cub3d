/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:54:20 by jhusso            #+#    #+#             */
/*   Updated: 2023/09/15 17:22:35 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

static void	init_line(t_line *line, t_ray *ray)
{
	line->x0 = ray->pix_x_pos;
	line->y0 = ray->pix_y_pos;
	line->x1 = ray->pix_x_pos + ray->pdx * 5 + 10; //  317;
	line->y1 = ray->pix_y_pos + ray->pdy * 5; //  317;
	printf("line->x0 = %i\n", line->x0);
	printf("line->y0 = %i\n", line->y0);
	printf("line->x1 = %i\n", line->x1);
	printf("line->y1 = %i\n", line->y1);

	line->dx = abs(line->x1 - line->x0);
	line->dy = -abs(line->y1 - line->y0);
	printf("line->dx = %i\n", line->dx);
	printf("line->dy = %i\n", line->dy);
	if (line->x1 > ray->pix_x_pos)
	{
		line->sx = 1;
		printf("line->sx = %i\n", line->sx);
	}
	else
	{
		line->sx = -1;
	}
	if (line->y1 > ray->pix_y_pos)
	{
		line->sy = 1;
		printf("line->sy = %i\n", line->sy);
	}
	else
	{
		line->sy = -1;
		printf("line->sy = %i\n", line->sy);
	}
	line->error = line->dx + line->dy;
	printf("line->error = %i\n", line->error);
	line->error2 = line->error * 2;
	printf("line.error2 = %i\n", line->error2);
}

void	bresenham(t_ray *ray)
{
	t_line line;

	init_line(&line, ray);
	printf("HERE!\n");
	while (42)
	{
		my_mlx_pixel_put(ray->cbd, line.x0, line.y0, 0x00000000);
		if (line.x0 == line.x1 && line.y0 == line.y1)
			break ;
		if (line.error2 <= line.dx)
		{
			line.error += line.dx;
			line.y0 += line.sy;
		}
		if (line.error2 >= line.dy)
		{
			line.error += line.dy;
			line.x0 += line.sx;
		}
	}
	printf("HERE after bresenhaims while!\n");
}

void	draw_nose(t_ray *ray)
{
	// if (ray->data->player_view == 'W')
	// 	ray->line->x1 += 20;
	bresenham(ray);
	// render_image(ray->cbd, ray, ray->data);
}
