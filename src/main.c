
#include "../include/map_validation.h"
#include "../include/cub3d.h"
#include "../mlx/mlx.h"
#include "../libft/libft.h"

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
	char	*line;
	char	*map_line;
	int		height;
	t_data	mv;
	t_cbd	cub;

	height = 0;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			return (-1);
		line = get_next_line(fd);
		map_line = ft_strdup(line);
		free(line);
		while (++height)
		{
			line = get_next_line(fd);
			if (!line)
				break ;
			map_line = ft_strjoin_gnl(map_line, line);
			free(line);
		}
		if (map_check(map_line, &mv) < 0)
			printf("map_validation_error\n");
		free(map_line);
		printf("here\n");
		mlx_functions(&cub);
		// init();
	}
	return (0);
}
