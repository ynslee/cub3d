/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:19:49 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/12 09:51:38 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

static void	angle_left_right(char *direction, t_ray *ray)
{
	if (!ft_strncmp_all(direction, "left"))
	{
		ray->pa = fix_angle(ray->pa + 5);
		ray->pdx = cos(deg_to_rad(ray->pa)) * PLAYER_S;
		ray->pdy = -sin(deg_to_rad(ray->pa)) * PLAYER_S;
	}
	else if (!ft_strncmp_all(direction, "right"))
	{
		ray->pa = fix_angle(ray->pa - 5);
		ray->pdx = cos(deg_to_rad(ray->pa)) * PLAYER_S;
		ray->pdy = -sin(deg_to_rad(ray->pa)) * PLAYER_S;
	}
}

static void	player_moves(int keysym, t_ray *ray)
{
	ray->pdx = cos(deg_to_rad(ray->pa)) * 20;
	ray->pdy = -sin(deg_to_rad(ray->pa)) * 20;
	if (keysym == 0) // LEFT
		move_sideway(ray, "left");
	if (keysym == 2) // RIGHT
		move_sideway(ray, "right");
	if (keysym == 13)
		move_frontback(ray, "up");
	if (keysym == 1)
		move_frontback(ray, "down");
	render_image(ray->cbd, ray, ray->data);
}

static void	angle_moves(int keysym, t_ray *ray)
{
	if (keysym == 123) // LEFT
		angle_left_right("left", ray);
	if (keysym == 124) // RIGHT
		angle_left_right("right", ray);
	if (keysym == 126) // UP
		move_frontback(ray, "up");
	if (keysym == 125) // DOWN
		move_frontback(ray, "down");
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
