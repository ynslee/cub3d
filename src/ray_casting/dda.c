/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 09:40:10 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/11 10:05:36 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

void	check_horizontal_gridline(t_ray *ray, t_line *line)
{
	line->x0 = ray->pix_x_pos;
	line->y0 = ray->pix_y_pos;
	line->x1 = 0;
	line->y1 = 0;
	ray->dof = 0;
	if (sin(deg_to_rad(ray->ra)) > 0.001) // going upwards
	{
		line->y1 = (int)(line->y0) / GRID_PIX * GRID_PIX - 0.0001;
		line->x1 = line->x0 + ((line->y0 - line->y1) * (1.0 / tan(deg_to_rad(ray->ra))));
		line->ya = -(GRID_PIX);
		line->xa = -line->ya * (1.0 / tan(deg_to_rad(ray->ra)));
	}
	else if (sin(deg_to_rad(ray->ra)) < -0.001) // going downwards
	{
		line->y1 = (int)(line->y0) / GRID_PIX * GRID_PIX + GRID_PIX;
		line->x1 = line->x0 + ((line->y0 - line->y1) * (1.0 / tan(deg_to_rad(ray->ra))));
		line->ya = GRID_PIX;
		line->xa = -line->ya * (1.0 / tan(deg_to_rad(ray->ra)));
	}
	else
	{
		line->x1 = line->x0;
		line->y1 = line->y0;
		ray->dof = 10000;
	}
	while (ray->dof < 10000)
	{
		if ((int)line->x1 / GRID_PIX >= 0 && \
		(int)line->x1 / GRID_PIX < ray->data->width && \
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

void	check_vertical_gridline(t_ray *ray, t_line *line)
{
	int		dof;

	dof = 0;
	line->x0 = ray->pix_x_pos;
	line->y0 = ray->pix_y_pos;
	line->v_x1 = 0;
	line->v_y1 = 0;
	if (cos(deg_to_rad(ray->ra)) > 0.001)
	{
		line->v_x1 = (int)(line->x0) / GRID_PIX * GRID_PIX + GRID_PIX;
		line->v_y1 = line->y0 + ((line->x0 - line->v_x1) * tan(deg_to_rad(ray->ra)));
		line->v_xa = GRID_PIX;
		line->v_ya = -line->v_xa * tan(deg_to_rad(ray->ra));
	}
	else if (cos(deg_to_rad(ray->ra)) < -0.001)
	{
		line->v_x1 = (int)(line->x0) / GRID_PIX * GRID_PIX - 0.0001;
		line->v_y1 = line->y0 + ((line->x0 - line->v_x1) * tan(deg_to_rad(ray->ra)));
		line->v_xa = -(GRID_PIX);
		line->v_ya = -line->v_xa * tan(deg_to_rad(ray->ra));
	}
	else
	{
		line->v_x1 = line->x0;
		line->v_y1 = line->y0;
		dof = 8;
	}
	while (dof < 8) 
	{
		if ((int)line->v_y1 / GRID_PIX >= 0 && \
		(int)line->v_y1 / GRID_PIX < ray->data->height && \
		is_wall(ray, line->v_x1, line->v_y1))
			dof = 8;
		else
		{
			line->v_y1 = (line->v_y1 + line->v_ya);
			line->v_x1 = (line->v_x1 + line->v_xa);
			dof += 1;
		}
	}
}

void	calculate_rays(t_ray *ray, t_line *line)
{
	float	h_length;
	float	v_length;

	h_length = sqrt(pow(line->x0 - line->x1, 2) + pow(line->y0 - line->y1, 2));
	v_length = sqrt(pow(line->x0 - line->v_x1, 2) + pow(line->y0 - line->v_y1, 2));
	printf("h_length is %f\n", h_length);
	printf("v_length is %f\n", v_length);
	printf("cos is %f\n", cos(deg_to_rad(ray->ra - ray->pa)));
	if (h_length != 0 && h_length < v_length) //this is added to remove fisheye distortion
	{
		ray->shortest = 'h';
		ray->distance = h_length * cos(deg_to_rad(ray->ra - ray->pa));
		line->x1 = (int)line->x1;
		line->y1 = (int)line->y1;
	}
	else if (v_length != 0)
	{
		ray->shortest = 'v';
		ray->distance = v_length * cos(deg_to_rad(ray->ra - ray->pa));
		line->x1 = (int)line->v_x1;
		line->y1 = (int)line->v_y1;
	}
	printf("ray->distance is %f\n", ray->distance);
	bresenham(ray, line, BLACK);
}
