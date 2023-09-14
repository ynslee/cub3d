/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:16:25 by jhusso            #+#    #+#             */
/*   Updated: 2023/09/13 16:16:55 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

void	init_render_utils(t_cbd *cbd, t_data *mv, t_ray *ray)
{
	cbd->mlx = mlx_init();
	if (!cbd->mlx)
		printf("Error connecting to mlx!\n");
	cbd->window = mlx_new_window(cbd->mlx, WIN_SIZE_X, WIN_SIZE_Y, "cub");
	if (cbd->window == NULL)
		printf("Error creating mlx window!\n");
	cbd->img = mlx_new_image(cbd->mlx, WIN_SIZE_X, WIN_SIZE_Y);
	if (!cbd->img)
		printf("Error creating mlx image!\n");
	cbd->img_addr = mlx_get_data_addr(cbd->img, &cbd->img_bpp,
			&cbd->img_len, &cbd->endian);
	if (!cbd->img_addr)
		printf("Error creating mlx image address!\n");
	set_hooks(cbd);
	mlx_loop(cbd->mlx);
	player_orientation_to_angle(mv, ray);
	ray->ra = fix_angle(ray->pa + FOV / 2); //starting point for rays, -- with rai
	ray->rai = fix_angle(FOV / WIN_SIZE_X); //iteration for next rays angle
	// draw_image(cbd, ray);
}
