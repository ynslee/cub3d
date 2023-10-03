/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:19:49 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/03 16:04:54 by yoonslee         ###   ########.fr       */
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

// int	side_wall_check(t_ray *ray, t_vector *next, float degree)
// {
// 	//check to see if the player is trying to pass through the wall
// }

/**
 * @brief check if next movement is movable
 * 
 * @param x next x position
 * @param y next y position
 * @return returns 1 if movable, if not, returns 0
 */
int	movable(float x, float y, t_ray *ray)
{
	t_vector	next;
	t_vector	current;

	current.x = ray->pix_x_pos / GRID_PIX;
	current.y = ray->pix_y_pos / GRID_PIX;
	next.x = x / GRID_PIX;
	next.y = y / GRID_PIX;
	printf("current.x is %d(%f)\n", (int)current.x, current.x);
	printf("current.y is %d(%f)\n", (int)current.y, current.y);
	printf("next.x is %d(%f)\n", (int)next.x, next.x);
	printf("next.y is %d(%f)\n", (int)next.y, next.y);
	if (ray->data->map[(int)next.y][(int)next.x] && \
	ray->data->map[(int)next.y][(int)next.x] == '1')
		return (0);
	if (ray->data->map[(int)next.y][(int)next.x] == \
			ray->data->map[(int)next.y][(int)next.x])
		return (1);
	// else if (ray->pa == 45 || ray->pa == 135 || ray->pa == 225 || ray->pa == 315)
	// {
	// 	return (side_wall_check(ray, &next, ray->pa));
	// }
	return (1);
}

void	move_sideway(t_ray *ray, char *direction)
{
	double	angle;
	float	x;
	float	y;

	if (ft_strncmp_all(direction, "left"))
		angle = fix_angle(ray->pa - 90);
	else
		angle = fix_angle(ray->pa + 90);
	printf("x before is %f\n", ray->pix_x_pos / GRID_PIX);
	printf("y before is %f\n", ray->pix_y_pos / GRID_PIX);
	x = ray->pix_x_pos + (cos(deg_to_rad(angle)) * PLAYER_S);
	y = ray->pix_y_pos + (-sin(deg_to_rad(angle)) * PLAYER_S);
	printf("x is %f\n", x / GRID_PIX);
	printf("y is %f\n", y / GRID_PIX);
	if (movable(x, y, ray))
	{
		ray->pix_x_pos = x;
		ray->pix_y_pos = y;
	}
}

/**
 * @brief move forward and backwards as a player.
 *  pdx is divided by PLAYER_S so we slow down the player's movement. 
 * @param ray 
 * @param direction 
 */
void	move_frontback(t_ray *ray, char *direction)
{
	float	x;
	float	y;

	if (ft_strncmp_all(direction, "up"))
	{
		x = ray->pix_x_pos - ray->pdx / PLAYER_S;
		y = ray->pix_y_pos - ray->pdy / PLAYER_S;
	}
	else
	{
		x = ray->pix_x_pos + ray->pdx / PLAYER_S;
		y = ray->pix_y_pos + ray->pdy / PLAYER_S;
	}
	if (movable(x, y, ray))
	{
		ray->pix_x_pos = x;
		ray->pix_y_pos = y;
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
	// 	ray->pix_x_pos -= ray->pdx;d
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
