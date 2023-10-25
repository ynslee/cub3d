/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:19:49 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/25 09:44:39 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting_bonus.h"

/**
 * @brief calculate the next angle and moves player angle to 5 degrees.
 */
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

/**
 * @brief players movement of up, down, right, and left key
 *
 * @param keysym key code of WASD keys
 */
static void	player_moves(int keysym, t_ray *ray)
{
	ray->pdx = cos(deg_to_rad(ray->pa)) * 20;
	ray->pdy = -sin(deg_to_rad(ray->pa)) * 20;
	if (keysym == 0)
		move_sideway(ray, "left");
	if (keysym == 2)
		move_sideway(ray, "right");
	if (keysym == 13)
		move_frontback(ray, "up");
	if (keysym == 1)
		move_frontback(ray, "down");
	render_image(ray->cbd, ray);
}

/**
 * @brief moves the player's angle based on left and right key
 *
 * @param keysym keycode of arrow keys on the keyboard
 */
static void	angle_moves(int keysym, t_ray *ray)
{
	ray->pdx = cos(deg_to_rad(ray->pa)) * 20;
	ray->pdy = -sin(deg_to_rad(ray->pa)) * 20;
	if (keysym == 123)
		angle_left_right("left", ray);
	if (keysym == 124)
		angle_left_right("right", ray);
	if (keysym == 126)
		move_frontback(ray, "up");
	if (keysym == 125)
		move_frontback(ray, "down");
	render_image(ray->cbd, ray);
}

int	key_event(int keysym, t_ray *ray, t_cub *cub)
{
	if (keysym == K_ESC)
		mlx_exit(ray, cub, "*** Thank you for playing! ***\n", 0);
	player_moves(keysym, ray);
	angle_moves(keysym, ray);
	return (0);
}

/**
 * @brief Set the hooks for the key events
 */
void	set_hooks(t_cbd *cbd, t_ray *ray, t_cub *cub)
{
	(void)cub;
	mlx_hook(cbd->window, 17, 1L << 5, &mlx_exit, ray);
	mlx_hook(cbd->window, 2, 1L << 0, &key_event, ray);
	mlx_hook(cbd->window, 4, 1L << 2, &mouse_press, ray);
	mlx_hook(ray->cbd->window, 6, 1L << 6, &mouse_event, ray);
	mlx_hook(ray->cbd->window, 5, 1L << 3, &mouse_release, ray);
}
