/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:27:53 by jhusso            #+#    #+#             */
/*   Updated: 2023/09/15 12:50:37 by yoonslee         ###   ########.fr       */
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
			my_mlx_pixel_put(cbd, y + ray->pix_y_pos, x + \
			ray->pix_x_pos, 0x00000000);
			y++;
		}
		x++;
	}
}

// static void	horixontal_ray(t_cbd *cbd, t_ray *ray)
// {
// 	t_vector	*line;
	
	
// }

// void	draw_rays(t_cbd *cbd, t_ray *ray)
// {
// 	ray->ra = fix_angle(ray->pa - FOV / 2);
// 	horizontal_ray(cbd, &ray);
// }
