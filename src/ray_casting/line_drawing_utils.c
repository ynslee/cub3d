/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:54:20 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/03 08:56:34 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

static void	init_line(t_line *line, t_ray *ray)
{
	line->x0 = ray->pix_x_pos;
	line->y0 = ray->pix_y_pos;

	line->x1 = ray->pix_x_pos + (ray->pdx * 20);
	line->y1 = ray->pix_y_pos + (ray->pdy * 20);
	line->dx = abs(line->x1 - line->x0);
	line->dy = abs(line->y1 - line->y0) * -1;
	if (line->x1 > ray->pix_x_pos)
		line->sx = 1;
	else
		line->sx = -1;
	if (line->y1 > ray->pix_y_pos)
		line->sy = 1;
	else
		line->sy = -1;
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
