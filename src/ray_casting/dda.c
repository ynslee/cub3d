/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 09:40:10 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/06 10:46:04 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

void	check_horizontal_gridline(t_ray *ray)
{
	/* finding the first intersection cordinates */
	t_line	line;

	init_line(&line, ray);
	if (ray->ra >= 0 && ray->ra < 181) // going upwards
	{
		printf("line->y0: %f\n", line.y0 / GRID_PIX * GRID_PIX);
		line.y1 = (int)(line.y0 / GRID_PIX) * GRID_PIX -1; //if y1 is part of the block above the grid line needs to add 1?
		line.ya = -(GRID_PIX);
	}
	if (ray->ra > 180 && ray->ra <= 360)
	{
		line.y1 = floor(line.y0 / GRID_PIX) * GRID_PIX + GRID_PIX;
		line.ya = GRID_PIX;
	}
	line.x1 = line.x0 + (line.y0 - line.y1) / tan(ray->ra);
	while (!is_wall(ray, line.x1, line.y1))
	{
		// if no wall at (x1, y1) increment to new (x1, y1) coordinates
		line.xa = GRID_PIX / tan(ray->ra);
		line.y1 = (line.y1 + line.ya) / GRID_PIX;
		line.x1 = (line.x1 + line.xa) / GRID_PIX;
	}
	printf("MOIKKA\n");
	bresenham(ray, &line, BLACK);
	// if wall at (x1, y1), return to caller function
}
