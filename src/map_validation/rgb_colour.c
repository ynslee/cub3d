/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_colour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:47:53 by yoonslee          #+#    #+#             */
/*   Updated: 2023/10/13 12:29:54 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map_validation.h"
#include "../../include/cub3d.h"

void	init_textures(t_cub *cub, t_cbd *cbd, t_data *data)
{
	char	*temp;

	temp  = ft_strjoin("./", cub->no);
	data->no_tex = mlx_xpm_file_to_image(cbd->mlx, &temp, &data->img_width, &data->img_width);
	free(temp);
	temp = ft_strjoin("./", cub->so);
	data->so_tex = mlx_xpm_file_to_image(cbd->mlx, &temp, &data->img_width, &data->img_width);
	free(temp);
	temp = ft_strjoin("./", cub->we);
	data->we_tex = mlx_xpm_file_to_image(cbd->mlx, &temp, &data->img_width, &data->img_width);
	free(temp);
	temp = ft_strjoin("./", cub->ea);
	data->ea_tex = mlx_xpm_file_to_image(cbd->mlx, &temp, &data->img_width, &data->img_width);
	free(temp);
}

unsigned int	rgb_colour(int *arr)
{
	unsigned int	colour;

	colour = ((arr[0] & 0xff) << 16) + ((arr[1] & 0xff) << 8) + (arr[2] & 0xff);
	return (colour);
}

unsigned int	change_colour(char *colour)
{
	int				*colour_arr;
	char			**colour_str;
	unsigned int	rgb;

	colour_str = ft_split(colour, ',');
	colour_arr = ft_calloc(3, sizeof(int));
	colour_arr[0] = ft_atoi(colour_str[0]);
	colour_arr[1] = ft_atoi(colour_str[1]);
	colour_arr[2] = ft_atoi(colour_str[2]);
	rgb = rgb_colour(colour_arr);
	free(colour_arr);
	free_char_array(colour_str);
	return (rgb);
}
