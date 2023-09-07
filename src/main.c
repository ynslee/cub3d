#include "cub3d.h"

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
		printf("cub->map_str =\n%s\n", cub->map_str);
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

int main(int argc, char **argv)
{
	int		fd;
	t_cub	cub;

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
		// if (valid_elements(fd) == -1)
		// 	printf("Elements not valid\n");
	}
	return (0);
}
