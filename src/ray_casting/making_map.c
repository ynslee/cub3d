
#include "ray_casting.h"
#include "cub3d.h"

static void	init_image(t_cbd *cbd)
{
	cbd->img_len = 64;
	cbd->background = mlx_xpm_file_to_image(cbd->mlx, \
		"../textures/simple/grey.xpm", &cbd->img_len, &cbd->img_len);
	cbd->wall = mlx_xpm_file_to_image(cbd->mlx, "../textures/simple/black.xpm", \
				&cbd->img_len, &cbd->img_len);
}

static void	put_image(t_cbd *cbd, char c, int x, int y)
{
	if (c == '1')
		mlx_put_image_to_window(cbd->mlx, cbd->window, cbd->wall, x, y);
	else
		mlx_put_image_to_window(cbd->mlx, cbd->window, cbd->background, x, y);
}

void	make_map(t_cbd *cbd, t_data *mv)
{
	int	i;
	int	j;

	i = 0;
	init_image(cbd);
	while (i > mv->height)
	{
		j = 0;
		while (j < mv->width)
		{
			put_image(cbd, mv->map[i][j], j * 64, i * 64);
			j++;
		}
		i++;
	}
}

int	close_game(t_cbd *cbd)
{
	mlx_destroy_window(cbd->mlx, cbd->window);
	exit(0);
	return (0);
}
