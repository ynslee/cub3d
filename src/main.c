
#include "../include/map_validation.h"
#include "../include/cub3d.h"

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

void	free_struct(t_cub *cub)
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
		print_struct(&cub);
		map_check(&cub, &mv, &cbd);
		if (mv.height * GRID_PIX > WIN_SIZE_Y || mv.width * GRID_PIX > WIN_SIZE_X)
		{
			printf("map is bigger than the window size\n");
			return (-1);
		}
		init_render_utils(&cbd, &mv, &cub);
		// printf("map copy:\n");
		// int k = -1;
		// while (++k < mv.height)
		// 	printf("%s\n", mv.map_cpy[k]);
		// printf("ft_atoi(argv[1]) = %i\n", ft_atoi(argv[1]));
		free_struct(&cub);
		free_mv_struct(&mv);
	}
	return (0);
}
