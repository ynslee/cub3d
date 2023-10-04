/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:33:18 by yoonslee          #+#    #+#             */
/*   Updated: 2023/10/04 15:49:19 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

void	draw_background(t_ray *ray)
{
	int				x;
	int				y;
	unsigned int	color;

	y = 0;
	color = ray->data->ceiling_rgb;
	while (y < WIN_SIZE_Y)
	{
		if (y > WIN_SIZE_Y / 2)
			color = ray->data->floor_rgb;
		x = -1;
		while (++x < WIN_SIZE_X)
		{
			my_mlx_pixel_put(ray->cbd, x, y, color);
		}
		y++;
	}
}

// void	init_xpm_images(t_data *data)
// {
// 	void(data);
// }