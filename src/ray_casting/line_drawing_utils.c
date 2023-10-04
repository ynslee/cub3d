/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:54:20 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/04 09:50:58 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

static void	init_line(t_line *line, t_ray *ray)
{

	line->x0 = ray->pix_x_pos;
	line->y0 = ray->pix_y_pos;
	line->x1 = ray->r_end_x;
	line->y1 = ray->r_end_y;
	// line->x1 = ray->pix_x_pos + ray->pdx;
	// line->y1 = ray->pix_y_pos + ray->pdy;
	// ray->ra = fix_angle(ray->pa - FOV / 2);
	line->dx = ft_abs(line->x1 - line->x0);
	if (line->x1 > line->x0)
		line->sx = 1;
	else
		line->sx = -1;
	line->dy = -ft_abs(line->y1 - line->y0);
	if (line->y1 > line->y0)
		line->sy = 1;
	else
		line->sy = -1;
	line->error = line->dx + line->dy;
	line->error2 = line->error * 2;
}

void	bresenham(t_ray *ray)
{
	t_line	line;

	init_line(&line, ray);
	while (42)
	{
		my_mlx_pixel_put(ray->cbd, line.x0, line.y0, 0x00000000);
		if ((int)line.x0 == (int)line.x1 && (int)line.y0 == (int)line.y1)
			break ;
		line.error2 = line.error * 2;
		if (line.error2 <= (int)line.dx)
		{
			line.error += (int)line.dx;
			line.y0 += (int)line.sy;
		}
		if (line.error2 >= (int)line.dy)
		{
			line.error += (int)line.dy;
			line.x0 += line.sx;
		}
	}
}

// void	draw_nose(t_ray *ray)
// {
// 	bresenham(ray);
// 	// render_image(ray->cbd, ray, ray->data);
// }
