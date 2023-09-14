/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:27:53 by jhusso            #+#    #+#             */
/*   Updated: 2023/09/14 10:51:20 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

void	draw_player(t_cbd *cbd, t_ray *ray)
{
	int	x = 0;
	int	y = 0;

	(void)cbd;
	while (x < 5)
	{
		y = 0;
		while (y < 5)
		{
			my_mlx_pixel_put(cbd, x + ray->data->player_x, y + ray->data->player_y, 0x00000000);
			y++;
		}
		x++;
	}
}

void	draw_image(t_cbd *cbd, t_ray *ray)
{
	(void)cbd;
	//draw_map
	draw_player(cbd, ray);
	draw_nose()
}
