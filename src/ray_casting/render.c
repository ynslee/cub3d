/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:16:25 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/17 12:21:59 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

void	render_image(t_cbd *cbd, t_ray *ray, t_data *mv)
{
	t_line	line;

	mlx_clear_window(cbd->mlx, cbd->window);
	draw_background(ray);
	ray->ray_count = 0;
	ray->ra = fix_angle(ray->pa - FOV / 2);
	while (ray->ray_count < WIN_SIZE_X)
	{
		check_inits(ray, &line);
		check_horizontal_gridline(ray, &line);
		check_vertical_gridline(ray, &line);
		compare_draw_rays(ray, &line);
		draw_image(ray, &line);
		ray->ray_count += 1;
		ray->ra = fix_angle(ray->ra + (float)FOV / (float)WIN_SIZE_X);
	}
	ray->ra = fix_angle(ray->pa - FOV / 2);
	make_mini_map(cbd, mv);
	cast_rays(ray);
	draw_player(cbd, ray);
	mlx_put_image_to_window(cbd->mlx, cbd->window, cbd->img, 0, 0);
}

void	init_ray_struct(t_ray *ray, t_data *data, t_cbd *cbd, t_line *line)
{
	t_vector	vector;

	player_orientation_to_angle(data, ray);
	ray->ra = fix_angle(ray->pa - FOV / 2);
	ray->dof = 0;
	ray->ray_count = 0;
	ray->data = (t_data *)data;
	ray->cbd = (t_cbd *)cbd;
	ray->vector = &vector;
	ray->line = (t_line *)line;
	ray->distance = 0;
	ray->wall_height = 0;
	ray->pix_x_pos = GRID_PIX * ray->data->player_y + GRID_PIX / 2;
	ray->pix_y_pos = GRID_PIX * ray->data->player_x + GRID_PIX / 2;
	ray->center_width = WIN_SIZE_X / 2;
	ray->center_height = WIN_SIZE_Y / 2;
}

void	init_render_utils(t_cbd *cbd, t_data *mv, t_cub *cub)
{
	t_ray	ray;
	t_line	line;

	init_ray_struct(&ray, mv, cbd, &line);
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
	init_textures(cub, cbd, mv);
	render_image(cbd, &ray, mv);
	set_hooks(cbd, &ray);
	mlx_loop(cbd->mlx);
}
