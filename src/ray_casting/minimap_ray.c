/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:54:20 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/17 12:28:39 by yoonslee         ###   ########.fr       */
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
	line->x0 = (int)(ray->pix_x_pos / 4);
	line->y0 = (int)(ray->pix_y_pos / 4);
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
	while (42)
	{
		my_mlx_pixel_put(ray->cbd, (int)line->x0, (int)line->y0, color);
		if ((int)line->x0 == (int)ray->r_end_x && \
		(int)line->y0 == (int)ray->r_end_y)
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

static int	bh_hit_wall(t_ray *ray, float x, float y)
{
	if (((int)(ray->pix_x_pos / MINI_PIX) == (int)(x / MINI_PIX)) && ((int)(ray->pix_y_pos / MINI_PIX) == (int)(y / MINI_PIX)))
		return (0);
	if ((ray->data->map[(int)(y / MINI_PIX - 0.01)][(int)x / MINI_PIX] == '1') || \
		(ray->data->map[(int)(y / MINI_PIX + 0.01)][(int)x / MINI_PIX] == '1') || \
		(ray->data->map[(int)y / MINI_PIX][(int)(x / MINI_PIX - 0.01)] == '1') || \
		(ray->data->map[(int)y / MINI_PIX][(int)(x / MINI_PIX + 0.01)] == '1'))
		return (1);
	return(0);
}

void	cast_rays(t_ray *ray)
{
	float	x;
	float	y;

	x = ray->pix_x_pos / 4;
	y = ray->pix_y_pos / 4;
	ray->ray_count = 0;
	while (ray->ray_count < (ray->data->width * MINI_PIX))
	{
		ray->pdx = cos(deg_to_rad(ray->ra)) * 0.2;
		ray->pdy = -sin(deg_to_rad(ray->ra)) * 0.2;
		x += ray->pdx;
		y += ray->pdy;
		if (ray->data->map[(int)y / MINI_PIX][(int)x / MINI_PIX] == '1' \
		|| bh_hit_wall(ray, x, y))
		{
			ray->r_end_x = floor(x);
			ray->r_end_y = floor(y);
			bresenham(ray, ray->line, BLACK);
			ray->ray_count += 1;
			ray->ra = fix_angle(ray->ra + \
			(float)FOV / (ray->data->width * MINI_PIX));
			x = ray->pix_x_pos / 4;
			y = ray->pix_y_pos / 4;
		}
	}
}
