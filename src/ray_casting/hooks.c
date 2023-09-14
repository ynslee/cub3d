/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:19:49 by jhusso            #+#    #+#             */
/*   Updated: 2023/09/14 12:44:59 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

void	arrow_moves(int keysym, t_ray *ray)
{
	if (keysym == 123 || keysym == 0) // LEFT
		ray->data->player_y = ray->data->player_y - 1;
	if (keysym == 124 || keysym == 2) // RIGHT
		ray->data->player_y = ray->data->player_y + 1;
	if (keysym == 126 || keysym == 13) // UP
		ray->data->player_x = ray->data->player_x - 1;
	if (keysym == 125 || keysym == 1) // DOWN
		ray->data->player_x = ray->data->player_x + 1;
	render_image(ray->cbd, ray, ray->data);
}

int	key_event(int keysym, t_ray *ray)
{
	if (keysym == K_ESC)
		destroy_flag(ray->cbd, 0);
	arrow_moves(keysym, ray);
	return (0);
}

void	set_hooks(t_cbd *cbd, t_ray *ray)
{
	mlx_hook(cbd->window, 17, 1L << 5, &destroy, cbd);
	mlx_key_hook(cbd->window, &key_event, ray);
	// mlx_mouse_hook(mlx->win_ptr, &mouse_event, mlx);
	// mlx_hook(mlx->win_ptr, 06, 1, &mouse_params, &mlx);
}
