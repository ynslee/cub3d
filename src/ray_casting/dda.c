/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 09:40:10 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/09 14:36:32 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

//we need to do something about when x1 and y1 goes to minus! :)
void	check_horizontal_gridline(t_ray *ray, t_line *line)
{
	/* finding the first intersection cordinates */

	printf("*****IN CHECK HORIZONTAL GRIDLINE*****\n");
	// printf("ray->pa: %f\n", ray->pa);
	// printf("ray->ra: %f\n", ray->ra);
	line->x0 = ray->pix_x_pos;
	line->y0 = ray->pix_y_pos;
	printf("line x0 value is %f\n", line->x0);
	printf("line y0 value is %f\n", line->y0);
	line->x1 = 0;
	line->y1 = 0;
	if (sin(deg_to_rad(ray->ra)) > 0.001) // going upwards
	{
		line->y1 = (int)line->y0 / GRID_PIX * GRID_PIX - GRID_PIX;
		line->x1 = line->x0 + ((line->y0 - line->y1) / tan(deg_to_rad(ray->ra)));
		line->ya = -(GRID_PIX);
	}
	else if (sin(deg_to_rad(ray->ra)) < -0.001) // going downwards
	{
		line->y1 = (int)(line->y0) / GRID_PIX * GRID_PIX + GRID_PIX;
		line->x1 = line->x0 + ((line->y0 - line->y1) / tan(deg_to_rad(ray->ra)));
		line->ya = GRID_PIX;
	}
	// printf("line->x1 is %f\n", line->x1);
	// printf("line->y1 is %f\n", line->y1);
	else //if (line->x1 <= 0 || line->x1 >= ray->data->width)
	{
		printf("coming here!\n");
		line->x1 = line->x0;
		line->y1 = line->y0;
		ray->dof = 100000;
		return ;
	}
	// printf("x grid pos: %d\n", (int)(line->x1 / GRID_PIX));
	// printf("y grid pos: %d\n", (int)(line->y1 / GRID_PIX));
	while (!is_wall(ray, line->x1, line->y1) && ray->dof < 100000)
	{
		line->x1 = (line->x1 + line->xa); /// GRID_PIX;
		line->y1 = (line->y1 + line->ya); /// GRID_PIX;
	}
	bresenham(ray, &line, BLACK);
}

// void	check_vertical_gridline(t_ray *ray)
// {
// 	/* finding the first intersection cordinates */
// 	t_line	line;

// 	line.x0 = ray->pix_x_pos;
// 	line.y0 = ray->pix_y_pos;
// 	line.x1 = 0;
// 	line.y1 = 0;
// 	printf("ray->pa: %f\n", ray->pa);
// 	printf("ray->ra: %f\n", ray->ra);
// 	if (cos(deg_to_rad(ray->ra) > 0.001)) //right pointing diagonal line like this /
// 	{
// 		line.x1 = (int)(line.x0) / GRID_PIX * GRID_PIX + GRID_PIX;
// 		line.y1 = line.y0 + ((line.x0 - line.x1) * tan(deg_to_rad(ray->ra)));
// 		line.xa = GRID_PIX;
// 	}
// 	else if (cos(deg_to_rad(ray->ra) < -0.001)) //left pointing diagonal line like this '\'
// 	{
// 		line.x1 = (int)(line.x0) / GRID_PIX * GRID_PIX - 1; //if y1 is part of the block above the grid line needs to add 1?
// 		line.y1 = line.y0 + ((line.x0 - line.x1) * tan(deg_to_rad(ray->ra)));
// 		line.xa = -(GRID_PIX);
// 	}
// 	while (42)
// 	{
// 		printf("line.x1 is %f\n", line.x1);
// 		printf("line.y1 is %f\n", line.y1);
// 		//from the print out, you'll see it segfaults when line.x1 and line.y1 is minus. we need to do something to make sure that it won't go under 0.
// 		line.ya = GRID_PIX * tan(deg_to_rad(ray->ra));
// 		if (is_wall(ray, line.x1 + line.xa, line.y1 + line.ya))  //this is added here so we won't go draw the line if there is wall. But it segfaults after three angle moves.
// 			break ;
// 		line.y1 = (line.y1 + line.ya) / GRID_PIX;
// 		line.x1 = (line.x1 + line.xa) / GRID_PIX;
// 	}
// 	bresenham(ray, &line, BLACK);
// 	// if wall at (x1, y1), return to caller function
// }
