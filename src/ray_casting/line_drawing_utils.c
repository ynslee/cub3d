/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:54:20 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/06 11:31:09 by yoonslee         ###   ########.fr       */
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

	line->x0 = (int)line->x0;
	line->y0 = (int)line->y0;
	line->x1 = (int)line->x1;
	line->y1 = (int)line->y1;
	// line->x1 = ray->pix_x_pos + ray->pdx;
	// line->y1 = ray->pix_y_pos + ray->pdy;
	ray->ra = fix_angle(ray->pa - FOV / 2);
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
	printf("line.x0 is %f\n", line->x0);
	printf("line.y0 is %f\n", line->y0);
	printf("line.x1 is %f\n", line->x1);
	printf("line.y1 is %f\n", line->y1);
	printf("line.error is %d\n", line->error);
	printf("line.error2 is %d\n", line->error2);
	printf("line.dx is %d\n", line->dx);
	printf("line.dy is %d\n", line->dy);
	printf("line.sx is %d\n", line->sx);
	printf("line.sy is %d\n", line->sy);
	while (42)
	{
		my_mlx_pixel_put(ray->cbd, (int)line->x0, (int)line->y0, color);
		if ((int)line->x0 == (int)line->x1 && (int)line->y0 == (int)line->y1)
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
