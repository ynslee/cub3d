/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:00:33 by yoonslee          #+#    #+#             */
/*   Updated: 2023/11/02 14:07:48 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/ray_casting_bonus.h"

/**
 * @brief rernders the image when opens the screen or the key is used.
 * renders the ceiling and floor, then draw the wall image with xpm files,
 * then draws the minimap on the top
 */
void	render_image_b(t_cbd *cbd, t_ray *ray)
{
	t_line	line;
	int		door;

	mlx_clear_window(cbd->mlx, cbd->window);
	draw_background(ray);
	ray->ray_count = 0;
	ray->ra = fix_angle(ray->pa - FOV / 2);
	while (ray->ray_count < WIN_SIZE_X)
	{
		check_inits(ray, &line);
		check_horizontal_gridline_b(ray, &line);
		check_vertical_gridline_b(ray, &line);
		door = 0;
		door = compare_draw_rays_b(ray, &line, door);
		draw_image_b(ray, &line, door);
		ray->ray_count += 1;
		ray->ra = fix_angle(ray->ra + (float)FOV / (float)WIN_SIZE_X);
	}
	ray->ra = fix_angle(ray->pa - FOV / 2);
	ray->ray_count = 0;
	make_mini_map(cbd, ray->data);
	cast_rays(ray);
	draw_player(cbd, ray);
	mlx_put_image_to_window(cbd->mlx, cbd->window, cbd->img, 0, 0);
}

/**
 * @brief initialise the ray struct
 *
 * @param ray stores pixel positon of x, y for DDA algorithm and bresenhamm algo
 */
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
	ray->mou_x = 0;
	ray->dragging = 0;
}

/**
 * @brief initialise all the utility to start rendering.
 *
 * @param cbd mlx, window ins initialised
 * @param mv position of x, y on the map and width and height of the
 * map is stored
 * @param cub stores the xpm image's address for this function
 */
void	init_render_utils_b(t_cbd *cbd, t_data *mv, t_cub *cub)
{
	t_ray	ray;
	t_line	line;

	init_ray_struct(&ray, mv, cbd, &line);
	cbd->mlx = mlx_init();
	if (!cbd->mlx)
		mlx_exit_b(&ray, cub, "Error connecting to mlx!\n", 1);
	cbd->window = mlx_new_window(cbd->mlx, WIN_SIZE_X, WIN_SIZE_Y, "cub");
	if (cbd->window == NULL)
		mlx_exit_b(&ray, cub, "Error creating mlx window!\n", 1);
	cbd->img = mlx_new_image(cbd->mlx, WIN_SIZE_X, WIN_SIZE_Y);
	if (!cbd->img)
		mlx_exit_b(&ray, cub, "Error creating mlx image!\n", 1);
	cbd->img_addr = mlx_get_data_addr(cbd->img, &cbd->img_bpp,
			&cbd->img_len, &cbd->endian);
	if (!cbd->img_addr)
		mlx_exit_b(&ray, cub, "Error creating mlx image address!\n", 1);
	init_textures_b(cub, &ray);
	render_image_b(cbd, &ray);
	set_hooks(cbd, &ray, cub);
	mlx_loop(cbd->mlx);
}
