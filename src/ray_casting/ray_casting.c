/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonseonlee <yoonseonlee@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 09:40:10 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/26 03:21:43 by yoonseonlee      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

/**
 * @brief initialise the line struct for the DDA algorithm
 */
void	check_inits(t_ray *ray, t_line *line)
{
	line->x0 = ray->pix_x_pos;
	line->y0 = ray->pix_y_pos;
	line->x1 = 0;
	line->y1 = 0;
	line->v_x1 = 0;
	line->v_y1 = 0;
	ray->dof = 0;
	ray->d_tan = 0;
}

/**
 * @brief check if the ray hits the wall and returns the value accordingly
 */
static void	hray_hits_wall(t_ray *ray, t_line *line)
{
	while (ray->dof < 10000)
	{
		if ((int)line->x1 / GRID_PIX >= 0 && \
		(int)line->y1 / GRID_PIX >= 0 && \
		(int)line->x1 / GRID_PIX < ray->data->width && \
		(int)line->y1 / GRID_PIX < ray->data->height && \
		is_wall(ray, line->x1, line->y1))
			ray->dof = 10000;
		else
		{
			line->x1 = (line->x1 + line->xa);
			line->y1 = (line->y1 + line->ya);
			ray->dof += 1;
		}
	}
}

/**
 * @brief check if the ray hits the wall and returns the value accordingly
 */
static void	vray_hits_wall(t_ray *ray, t_line *line)
{
	while (ray->dof < 10000)
	{
		if ((int)line->v_y1 / GRID_PIX >= 0 && \
		(int)line->v_x1 / GRID_PIX >= 0 && \
		(int)line->v_y1 / GRID_PIX < ray->data->height && \
		(int)line->v_x1 / GRID_PIX < ray->data->width && \
		is_wall(ray, line->v_x1, line->v_y1))
			ray->dof = 10000;
		else
		{
			line->v_y1 = (line->v_y1 + line->v_ya);
			line->v_x1 = (line->v_x1 + line->v_xa);
			ray->dof += 1;
		}
	}
}

/**
 * @brief calculate the x and y's first wall-hitting position of
 * horizontal grid line
 */
void	check_horizontal_gridline(t_ray *ray, t_line *line)
{
	if (tan(deg_to_rad(ray->ra)))
		ray->d_tan = 1.0 / tan(deg_to_rad(ray->ra));
	if (sin(deg_to_rad(ray->ra)) > 0.001)
	{
		line->y1 = (int)(line->y0) / GRID_PIX * GRID_PIX - 0.0001;
		line->x1 = line->x0 + (line->y0 - line->y1) * ray->d_tan;
		line->ya = -(GRID_PIX);
	}
	else if (sin(deg_to_rad(ray->ra)) < -0.001)
	{
		line->y1 = (int)(line->y0) / GRID_PIX * GRID_PIX + GRID_PIX;
		line->x1 = line->x0 + (line->y0 - line->y1) * ray->d_tan;
		line->ya = GRID_PIX;
	}
	else
	{
		line->x1 = line->x0;
		line->y1 = line->y0;
		ray->dof = 10000;
	}
	line->xa = -line->ya * ray->d_tan;
	hray_hits_wall(ray, line);
}

/**
 * @brief calculate the x and y's first wall-hitting position of vertical
 * grid line
 */
void	check_vertical_gridline(t_ray *ray, t_line *line)
{
	ray->dof = 0;
	if (cos(deg_to_rad(ray->ra)) > 0.001)
	{
		line->v_x1 = (int)(line->x0) / GRID_PIX * GRID_PIX + GRID_PIX;
		line->v_y1 = line->y0 + ((line->x0 - line->v_x1) * \
		tan(deg_to_rad(ray->ra)));
		line->v_xa = GRID_PIX;
	}
	else if (cos(deg_to_rad(ray->ra)) < -0.001)
	{
		line->v_x1 = (int)(line->x0) / GRID_PIX * GRID_PIX - 0.0001;
		line->v_y1 = line->y0 + ((line->x0 - line->v_x1) * \
		tan(deg_to_rad(ray->ra)));
		line->v_xa = -(GRID_PIX);
	}
	else
	{
		line->v_x1 = line->x0;
		line->v_y1 = line->y0;
		ray->dof = 10000;
	}
	line->v_ya = -line->v_xa * tan(deg_to_rad(ray->ra));
	vray_hits_wall(ray, line);
}
