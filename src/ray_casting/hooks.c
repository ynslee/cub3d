/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:19:49 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/03 12:23:35 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

static void	angle_left_right(char *direction, t_ray *ray)
{
	// printf("coming to angle_left_right\n");
	// printf("ray->pa: %f\nray->pdx: %f\nray->pdy: %f\n", ray->pa, ray->pdx, ray->pdy);
	if (!ft_strncmp_all(direction, "left"))
	{
		ray->pa = fix_angle(ray->pa + PLAYER_S);
		ray->pdx = cos(deg_to_rad(ray->pa)) * 20;
		ray->pdy = -sin(deg_to_rad(ray->pa)) * 20;
	}
	else if (!ft_strncmp_all(direction, "right"))
	{
		ray->pa = fix_angle(ray->pa - PLAYER_S);
		ray->pdx = cos(deg_to_rad(ray->pa)) * 20;
		ray->pdy = -sin(deg_to_rad(ray->pa)) * 20;
	}
}

/**
 * @brief check if next movement is movable
 * 
 * @param x next x position
 * @param y next y position
 * @return returns 1 if movable, if not, returns 1
 */
int	movable(int x, int y, t_ray *ray)
{
	return (1);
}

void	move_sideway(t_ray *ray, char *direction)
{
	double	angle;
	float	x;
	float	y;

	if (ft_strncmp_all(direction, "left"))
		angle = fix_angle(ray->pa + 90);
	else
		angle = fix_angle(ray->pa - 90);
	x = ray->pix_x_pos + cos(deg_to_rad(angle)) * PLAYER_S;
	y = ray->pix_y_pos + -sin(deg_to_rad(angle)) * PLAYER_S;
	if (movable(x, y, ray))
	{
		ray->pix_x_pos = x;
		ray->pix_x_pos = y;
	}
}

static void	player_moves(int keysym, t_ray *ray)
{
	if (keysym == 0) // LEFT
		move_sideway(ray, "left");
	if (keysym == 2) // RIGHT
		move_sideway(ray, "right");
	if (keysym == 13) // UP
		ray->pix_y_pos = ray->pix_y_pos - 1;
	if (keysym == 1) // DOWN
		ray->pix_y_pos = ray->pix_y_pos + 1;
	render_image(ray->cbd, ray, ray->data);
}

static void	angle_moves(int keysym, t_ray *ray)
{
	// ray->pdx = cos(deg_to_rad(ray->pa));
	// ray->pdy = -sin(deg_to_rad(ray->pa));
	if (keysym == 123) // LEFT
		angle_left_right("left", ray);
	if (keysym == 124) // RIGHT
		angle_left_right("right", ray);
	// if (keysym == 126) // UP
	// {
	// 	ray->pix_x_pos += ray->pdx;
	// 	ray->pix_y_pos += ray->pdy;
	// }
	// if (keysym == 125) // DOWN
	// {
	// 	ray->pix_x_pos -= ray->pdx;
	// 	ray->pix_y_pos -= ray->pdy;
	// }
	// ray->pdx = cos(deg_to_rad(ray->pa));
	// ray->pdy = -sin(deg_to_rad(ray->pa));
	render_image(ray->cbd, ray, ray->data);
}

int	key_event(int keysym, t_ray *ray)
{
	if (keysym == K_ESC)
		destroy_flag(ray->cbd, 0);
	player_moves(keysym, ray);
	angle_moves(keysym, ray);
	return (0);
}

void	set_hooks(t_cbd *cbd, t_ray *ray)
{
	mlx_hook(cbd->window, 17, 1L << 5, &destroy, cbd);
	mlx_hook(cbd->window, 2, 1L << 0, &key_event, ray);
	// mlx_mouse_hook(mlx->win_ptr, &mouse_event, mlx);
	// mlx_hook(mlx->win_ptr, 06, 1, &mouse_params, &mlx);
}
