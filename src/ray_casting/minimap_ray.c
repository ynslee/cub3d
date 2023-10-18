/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:54:20 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/18 11:18:14 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

/**
 * @brief returns the absolute value of the integer
 */
int	ft_abs(int a)
{
	if (a < 0)
		return (-1 * a);
	return (a);
}

/**
 * @brief initialise line struct for the bresenham drawing function
 */
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

/**
 * @brief draws the rays of player(60 degree angle). Uses player's
 * position and the position of hitting wall with ray's angle and draws
 * the line inbetween
 */
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

/**
 * @brief check if the x, y position hits the wall for bresenham function only
 * @return 0 if there is no wall, 1 if there is wall
 */
static int	bh_hit_wall(t_ray *ray, float x, float y)
{
	int	p;

	p = MINI_PIX;
	if (((int)(ray->pix_x_pos / MINI_PIX) == (int)(x / MINI_PIX)) && \
	((int)(ray->pix_y_pos / MINI_PIX) == (int)(y / MINI_PIX)))
		return (0);
	if ((ray->data->map[(int)(y / p - 0.01)][(int)x / p] == '1') || \
		(ray->data->map[(int)(y / p + 0.01)][(int)x / p] == '1') || \
		(ray->data->map[(int)y / p][(int)(x / p - 0.01)] == '1') || \
		(ray->data->map[(int)y / p][(int)(x / p + 0.01)] == '1'))
		return (1);
	return (0);
}

/**
 * @brief using bresenham's function to draw rays on the minimap
 *
 * @param x x's pixel position on the minimap
 * @param y y's pixel position on the minimap
 */
void	cast_rays(t_ray *ray)
{
	float	x;
	float	y;

	x = ray->pix_x_pos / 4;
	y = ray->pix_y_pos / 4;
	ray->ray_count = 0;
	while (ray->ray_count < (ray->data->width * MINI_PIX / 2))
	{
		ray->pdx = cos(deg_to_rad(ray->ra)) * 0.2;
		ray->pdy = -sin(deg_to_rad(ray->ra)) * 0.2;
		x += ray->pdx / 2;
		y += ray->pdy / 2;
		if (ray->data->map[(int)y / MINI_PIX][(int)x / MINI_PIX] == '1' \
		|| bh_hit_wall(ray, x, y))
		{
			ray->r_end_x = floor(x);
			ray->r_end_y = floor(y);
			bresenham(ray, ray->line, BLACK);
			ray->ray_count += 1;
			ray->ra = fix_angle(ray->ra + \
			(float)FOV / (ray->data->width * MINI_PIX / 2));
			x = ray->pix_x_pos / 4;
			y = ray->pix_y_pos / 4;
		}
	}
}
