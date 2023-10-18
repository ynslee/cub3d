/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:17:33 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/18 10:10:51 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"

/**
 * @brief puts the colour for on the wall based on x, y position
 *
 * @param x pixel position of x on the window
 * @param y pixel position of y on the window
 */
void	my_mlx_pixel_put(t_cbd *cbd, int x, int y, int color)
{
	char	*dst;

	if (WIN_SIZE_X <= x || x < 0 || y < 0 || y >= WIN_SIZE_Y)
		return ;
	dst = cbd->img_addr + (y * cbd->img_len + x * (cbd->img_bpp / 8));
	*(unsigned int *)dst = color;
}

/**
 * @brief find the pixel's colour for x and y position on the texture
 *
 * @param x texture's x position
 * @param y texture's y position
 * @return colour of the texture's pixel position
 */
unsigned int	my_mlx_pixel_get(t_tex_img *img, int x, int y)
{
	unsigned int	dst;

	if (x >= img->width || x < 0 || y >= img->height || y < 0)
		return (RED);
	dst = *(unsigned int *)(img->img_addr + (y * img->line_length + x * \
	(img->bpp / 8)));
	return (dst);
}

// static void	free_destroy_images(char)

static void	destroy_images(t_cbd *cbd, t_data *data)
{
	if (cbd->img)
	{
		mlx_destroy_image(cbd->mlx, cbd->img);
		cbd->img = NULL;
	}
	if (data->texture[NO])
		mlx_destroy_image(cbd->mlx, data->texture[NO]->img_ptr);
	if (data->texture[SO])
		mlx_destroy_image(cbd->mlx, data->texture[SO]->img_ptr);
	if (data->texture[EA])
		mlx_destroy_image(cbd->mlx, data->texture[EA]->img_ptr);
	if (data->texture[WE])
		mlx_destroy_image(cbd->mlx, data->texture[WE]->img_ptr);
}

/**
 * @brief destroys the window and mlx, then exits if there's error
 *
 */
int	mlx_exit(t_cbd *cbd, t_data *data, char *message, int flag)
{
	ft_putstr_fd(message, flag);
	(void)cbd;
	if (cbd->window)
	{
		mlx_destroy_window(cbd->mlx, cbd->window);
		cbd->window = NULL;
	}
	destroy_images(cbd, data);
	free_mv_struct(data);
	exit(flag);
}
