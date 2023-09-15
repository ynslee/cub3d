/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:19:49 by jhusso            #+#    #+#             */
/*   Updated: 2023/09/15 16:08:35 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

void	angle_left_right(char *direction, t_ray *ray)
{
	if (!ft_strncmp_all(direction, "left"))
	{
		ray->vector->pa -= 0.1;
		if (ray->vector->pa < 0)
			ray->vector->pa += 2 * M_PI;
		ray->pdx = cos(ray->vector->pa) * 5;
		ray->pdy = sin(ray->vector->pa) * 5;
	}
	else if (!ft_strncmp_all(direction, "right"))
	{
		ray->vector->pa += 0.1;
		if (ray->vector->pa > 2 * M_PI)
			ray->vector->pa -= 2 * M_PI;
		ray->pdx = cos(ray->vector->pa) * 5;
		ray->pdy = sin(ray->vector->pa) * 5;
	}
}

void	arrow_moves(int keysym, t_ray *ray)
{
	if (keysym == 0) // LEFT
		ray->pix_y_pos = ray->pix_y_pos - 1;
	if (keysym == 2) // RIGHT
		ray->pix_y_pos = ray->pix_y_pos + 1;
	if (keysym == 13) // UP
		ray->pix_x_pos = ray->pix_x_pos - 1;
	if (keysym == 1) // DOWN
		ray->pix_x_pos = ray->pix_x_pos + 1;
	render_image(ray->cbd, ray, ray->data);
}

void	angle_moves(int keysym, t_ray *ray)
{
	if (keysym == 123) // LEFT
		angle_left_right("left", ray);
	if (keysym == 124) // RIGHT
		angle_left_right("right", ray);
	if (keysym == 126) // UP
	{
		ray->pix_x_pos += ray->pdx;
		ray->pix_y_pos += ray->pdy;
	}
	if (keysym == 125) // DOWN
	{
		ray->pix_x_pos -= ray->pdx;
		ray->pix_y_pos -= ray->pdy;
	}
	render_image(ray->cbd, ray, ray->data);
}

int	key_event(int keysym, t_ray *ray)
{
	if (keysym == K_ESC)
		destroy_flag(ray->cbd, 0);
	arrow_moves(keysym, ray);
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
