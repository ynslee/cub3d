/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:54:20 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/12 09:37:12 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

void	init_line(t_line *line, t_ray *ray)
{
	(void)ray;
	// line->x0 = (int)line->x0;
	// line->y0 = (int)line->y0;
	line->x0 = (int)ray->pix_x_pos;
	line->y0 = (int)ray->pix_y_pos;
	line->x1 = (int)ray->r_end_x;
	line->y1 = (int)ray->r_end_y;
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

void	bresenham(t_ray *ray, t_line *line, int color)
{
	init_line(line, ray);
	// printf("COMING TO BRESENHAM\n");
	// printf("x0 and y0 \t%f\t%f\n", line->x0, line->y0);
	// printf("xend and yend \t%f\t%f\n", ray->r_end_x, ray->r_end_y);
	while (42)
	{
		my_mlx_pixel_put(ray->cbd, (int)line->x0, (int)line->y0, color);
		if ((int)line->x0 == (int)ray->r_end_x && (int)line->y0 == (int)ray->r_end_y)
			break ;
		line->error2 = (int)line->error * 2;
		if ((int)line->error2 <= (int)line->dx)
		{
			line->error += (int)line->dx;
			line->y0 += (int)line->sy;
		}
		if ((int)line->error2 >= (int)line->dy)
		{
			line->error += (int)line->dy;
			line->x0 += (int)line->sx;
		}
	}
}

// void	draw_nose(t_ray *ray)
// {
// 	bresenham(ray);
// 	// render_image(ray->cbd, ray, ray->data);
// }
