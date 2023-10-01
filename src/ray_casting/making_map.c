
#include "ray_casting.h"
#include "cub3d.h"


void	draw_grid(t_cbd *cbd, t_data *mv)
{
	int	x;
	int	y;

	x = 0;
	while (x < mv->width * 64)
	{
		y = -1;
		while (++y < mv->height * 64)
			my_mlx_pixel_put(cbd, x, y, BLACK);
		x = x + 64;
	}
	x = -1;
	while (++x < mv->width * 64)
	{
		y = 0;
		while (y < mv->height * 64)
		{
			my_mlx_pixel_put(cbd, x, y, BLACK);
			y = y + 64;
		}
	}
}

void	draw_map(t_cbd *cbd, int x, int y, int color)
{
	int	i;
	int	j;

	i = -1;
	// printf("in draw_map x: %i\ty: %i\n", x, y);
	while (++i < GRID_PIX)
	{
		j = -1;
		while (++j < GRID_PIX)
		{
			// printf("x:%i y:%i\n", i, j);
			my_mlx_pixel_put(cbd, x + i, y + j, color);
		}
	}

}

void	make_map(t_cbd *cbd, t_data *mv)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	printf("mv->height: %i\tmv->width: %i\n", mv->height, mv->width);
	while (i < mv->height) // i = y = height
	{
		printf("i: %i\n", i);
		j = 0;
		while (j < mv->width) // j = x = width
		{
			printf("j: %i\n", j);
			if (mv->map[i][j] == '1')
				color = BLUE;
			else
				color = LIGHTBLUE;
			draw_map(cbd, j * GRID_PIX, i * GRID_PIX, color);
			j++;
		}
		i++;
	}
	draw_grid(cbd, mv);
}
