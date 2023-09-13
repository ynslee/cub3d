/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 09:47:29 by jhusso            #+#    #+#             */
/*   Updated: 2023/09/13 11:48:56 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

float	fix_angle(float a)
{
	if (a < 0)
		a += 360;
	if (a > 359)
		a -= 360;
	printf("in fix angle: %f\n", a);
	return (a);
}

float	deg_to_rad(float a)
{
	return (a * M_PI / 180.0);
}
void	player_orientation_to_angle(t_data *mv, t_ray *ray)
{
	if (mv->player_view == 'N')
		ray->pa = 90.0;
	if (mv->player_view == 'S')
		ray->pa = 270.0;
	if (mv->player_view == 'W')
		ray->pa = 180.0;
	if (mv->player_view == 'E')
		ray->pa = 0.0;
	// printf("player angle = %f\n", ray->pa);
}

void	init_render_utils(t_cbd *cbd, t_data *mv, t_ray *ray)
{
	cbd->mlx = mlx_init();
	if (!cbd->mlx)
		printf("Error connecting to mlx!\n");
	cbd->window = mlx_new_window(cbd->mlx, WIN_SIZE_X, WIN_SIZE_Y, "cub");
	if (cbd->window == NULL)
		printf("Error creating mlx window!\n");
	player_orientation_to_angle(mv, ray);
	ray->ra = fix_angle(ray->pa + FOV / 2); //starting point for rays, -- with rai
	// ray->rai = fix_angle(FOV / WIN_SIZE_X); //iteration for next rays angle

}
