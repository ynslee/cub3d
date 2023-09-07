
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
	printf("*****************************\n");
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

static void	init_struct(t_cub *cub)
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

// void	init(void)
// {

// }

void	mlx_functions(t_cbd *cub)
{
	int	height;
	int	width;
	int	img_len;

	height = 512;
	width = 1024;
	img_len = 200;
	cub->mlx = mlx_init();
	printf("here2\n");
	cub->window = mlx_new_window(cub->mlx, width, height, \
				"cub3d");
	printf("here3\n");
	mlx_clear_window(cub->mlx, cub->window);
	printf("here4\n");
	cub->background = mlx_xpm_file_to_image(cub->mlx, "./grey.xpm", \
				&img_len, &img_len);
	printf("here5\n");
	mlx_put_image_to_window(cub->mlx, cub->window, cub->background, 0, 0);
	printf("here6\n");
}

int	main(int argc, char **argv)
{
	int		fd;
	t_cub	cub;
	t_data	mv;

	if (argc == 2)
	{
		fd = valid_file(argv[1]);
		if (fd == -1)
			printf("Invalid file\n");
		init_struct(&cub);
		if (valid_elements(fd, &cub) == -1)
			exit(0);
		print_struct(&cub);
		free_struct(&cub);
		free_mv_struct(&mv);
		// if (valid_elements(fd) == -1)
		// 	printf("Elements not valid\n");
	}
	return (0);
}
