/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:16:25 by jhusso            #+#    #+#             */
/*   Updated: 2023/09/15 16:12:15 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

// void	draw_background(t_cbd *cbd)
// {
// 	int	x = 0;
// 	int	y = 0;

// 	while (x < WIN_SIZE_X)
// 	{
// 		y = 0;
// 		while (y < WIN_SIZE_Y)
// 		{
// 			my_mlx_pixel_put(cbd, x, y, 0x0000FF00);
// 			y++;
// 		}
// 		x++;
// 	}
// }

void	render_image(t_cbd *cbd, t_ray *ray, t_data *mv)
{
	mlx_clear_window(cbd->mlx, cbd->window);
	make_map(cbd, mv);
	draw_player(cbd, ray);
	draw_nose(ray);
	// draw_background(cbd);
	// draw_image(cbd, ray);
	mlx_put_image_to_window(cbd->mlx, cbd->window, cbd->img, 0, 0);
}

void	init_ray_struct(t_ray *ray, t_data *data, t_cbd *cbd)
{
	t_vector	vector;

	ray->pa = 0;
	ray->ra = 0;
	ray->rai = 0;
	ray->data = (t_data *)data;
	ray->cbd = (t_cbd *)cbd;
	ray->vector = &vector;
	ray->pix_x_pos = GRID_PIX * ray->data->player_x + GRID_PIX / 2.5;
	ray->pix_y_pos = GRID_PIX * ray->data->player_y + GRID_PIX / 2.5;
	ray->center_width = WIN_SIZE_X / 2;
	ray->center_height = WIN_SIZE_Y / 2;
	ray->pdx = deg_to_rad(cos(ray->pa));
	ray->pdy = deg_to_rad(sin(ray->pa));
}

void	init_render_utils(t_cbd *cbd, t_data *mv)
{
	t_ray	ray;

	init_ray_struct(&ray, mv, cbd);
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
	render_image(cbd, &ray, mv);
	set_hooks(cbd, &ray);
	mlx_loop(cbd->mlx);
	player_orientation_to_angle(mv, &ray);
	// draw_rays(cbd, &ray);
	ray.rai = fix_angle(FOV / WIN_SIZE_X); //iteration for next rays angle
}
