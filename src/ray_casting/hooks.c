/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:19:49 by jhusso            #+#    #+#             */
/*   Updated: 2023/09/14 08:56:41 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

// void	arrow_moves(int keysym, t_mlx *mlx)
// {
// 	if (keysym == 123 || keysym == 0) // LEFT
// 		mlx->x = mlx->x - 5;
// 	if (keysym == 124 || keysym == 2) // RIGHT
// 		mlx->x = mlx->x + 5;
// 	if (keysym == 126 || keysym == 13) // UP
// 		mlx->y = mlx->y - 5;
// 	if (keysym == 125 || keysym == 1) // DOWN
// 		mlx->y = mlx->y + 5;
// 	render_img(mlx);
// }

int	key_event(int keysym, t_cbd *cbd)
{
	if (keysym == K_ESC)
		destroy_flag(cbd, 0);
	// arrow_moves(keysym, mlx);
	return (0);
}

void	set_hooks(t_cbd *cbd)
{
	mlx_hook(cbd->window, 17, 1L << 5, &destroy, cbd);
	mlx_key_hook(cbd->window, &key_event, cbd);
	// mlx_mouse_hook(mlx->win_ptr, &mouse_event, mlx);
	// mlx_hook(mlx->win_ptr, 06, 1, &mouse_params, &mlx);
}
