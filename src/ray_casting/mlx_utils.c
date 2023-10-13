/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:17:33 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/13 12:33:47 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

void	my_mlx_pixel_put(t_cbd *cbd, int x, int y, int color)
{
	char	*dst;

	dst = cbd->img_addr + (y * cbd->img_len + x * (cbd->img_bpp / 8));
	*(unsigned int *)dst = color;
}

void	my_mlx_pixel_get(t_cbd *cbd, int x, int y, int color)
{
	unsigned int	dst;

	dst = *(unsigned int *)(cbd->img_addr + (y * cbd->img_len + x * (cbd->img_bpp / 8)));
	return (dst);
}

int	destroy_flag(t_cbd *cbd, int flag)
{
	mlx_destroy_window(cbd->mlx, cbd->window);
	if (flag == 1)
		exit(1);
	else
		exit (0);
}

int	destroy(t_cbd *cbd)
{
	mlx_destroy_window(cbd->mlx, cbd->window);
	exit(0);
}
