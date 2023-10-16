/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_colour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:47:53 by yoonslee          #+#    #+#             */
/*   Updated: 2023/10/16 07:09:58 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map_validation.h"
#include "../../include/cub3d.h"

t_tex_img	*get_new_xpm_img(t_cbd *cbd, t_data *data, char *file_path)
{
	t_tex_img	*img;

	img = (t_tex_img *)ft_calloc(1, sizeof(t_tex_img));
	if (!img)
		printf("ERROR callocin\n");
	printf("");
	img->img_ptr = mlx_xpm_file_to_image(cbd->mlx, file_path, \
		 &(data->img_width), &(data->img_height));
	if (!img->img_ptr)
		printf("ERROR generating img_ptr to texture\n");
	img->img_addr = mlx_get_data_addr(img->img_ptr, &(img->bpp), \
		&(img->line_length), &(img->endian));
	if (!img->img_addr)
		printf("ERROR getting img_addres to texture\n");
	return (img);
}

/* init no, so, we, ea t_tex_img struct separately calling another function. */

void	init_textures(t_cub *cub, t_cbd *cbd, t_data *data)
{
	data->texture[NO] = get_new_xpm_img(cbd, data, cub->no);
	data->texture[SO] = get_new_xpm_img(cbd, data, cub->so);
	data->texture[WE] = get_new_xpm_img(cbd, data, cub->we);
	data->texture[EA] = get_new_xpm_img(cbd, data, cub->ea);

	// char	*temp;
	// temp  = ft_strjoin("./", cub->no);
	// data->no_tex = mlx_xpm_file_to_image(cbd->mlx, cub->no, &(data->img_width), &(data->img_height));
	// if (!data->no_tex)
	// 	printf("Can't convert xpm file to image\n");
	// free(temp);
	// temp = ft_strjoin("./", cub->so);
	// data->so_tex = mlx_xpm_file_to_image(cbd->mlx, &temp, &data->img_width, &data->img_width);
	// free(temp);
	// temp = ft_strjoin("./", cub->we);
	// data->we_tex = mlx_xpm_file_to_image(cbd->mlx, &temp, &data->img_width, &data->img_width);
	// free(temp);
	// temp = ft_strjoin("./", cub->ea);
	// data->ea_tex = mlx_xpm_file_to_image(cbd->mlx, &temp, &data->img_width, &data->img_width);
	// free(temp);
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
