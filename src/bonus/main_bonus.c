/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:44:33 by jhusso            #+#    #+#             */
/*   Updated: 2023/11/02 10:02:29 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	print_struct(t_cub *cub)
{
	printf("*****************************\n");
	if (cub->no)
		printf("cub->no = %s\n", cub->no);
	if (cub->so)
		printf("cub->so = %s\n", cub->so);
	if (cub->we)
		printf("cub->we = %s\n", cub->we);
	if (cub->ea)
		printf("cub->ea = %s\n", cub->ea);
	if (cub->f_color)
		printf("cub->f_color = %s\n", cub->f_color);
	if (cub->c_color)
		printf("cub->c_color = %s\n", cub->c_color);
	if (cub->map_str)
		printf("cub->map_str =\n%s", cub->map_str);
	printf("\n*****************************\n");
}

// static void print_maps(t_data * data)
// {
// 	int i = 0;
// 	printf("\n******* map_cpy ***********\n");
// 	while (data->map_cpy[i])
// 	{
// 		printf("%s\n", data->map_cpy[i]);
// 		i++;
// 	}
// 	i = 0;
// 	printf("\n******** buffer_cpy *************\n");
// 	while (data->buffer_cpy[i])
// 	{
// 		printf("%s\n", data->map_cpy[i]);
// 		i++;
// 	}
// }

void	free_cub_struct(t_cub *cub)
{
	if (cub->no)
		free(cub->no);
	if (cub->so)
		free(cub->so);
	if (cub->we)
		free(cub->we);
	if (cub->ea)
		free(cub->ea);
	if (cub->f_color)
		free(cub->f_color);
	if (cub->c_color)
		free(cub->c_color);
	if (cub->map_str)
		free(cub->map_str);
}

static void	init_cub_struct(t_cub *cub)
{
	cub->no = 0;
	cub->so = 0;
	cub->we = 0;
	cub->ea = 0;
	cub->f_color = 0;
	cub->c_color = 0;
	cub->id_flag = 0;
	cub->map_str = 0;
}

int	main(int argc, char **argv)
{
	int		fd;
	t_cub	cub;
	t_data	mv;
	t_cbd	cbd;

	if (argc == 2)
	{
		fd = valid_file(argv[1]);
		if (fd == -1)
			file_print_error(&cub, "Invalid file\n", 0);
		init_cub_struct(&cub);
		read_file(fd, &cub);
		map_check_b(&cub, &mv);
		init_render_utils_b(&cbd, &mv, &cub);
	}
	else
	{
		ft_putstr_fd("Wrong argument! put argument as such :", 2);
		ft_putstr_fd("./cub3D_bonus maps/good/(mapname).cub\n", 2);
	}
	return (0);
}
