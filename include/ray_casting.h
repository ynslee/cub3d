
#ifndef RAY_CASTING_H
# define RAY_CASTING_H

# define FOV 60
# define GRID_PIX 64
# define K_ESC 53

# define BLACK 0x000000
# define WHITE 0xffffff
# define GREEN 0x009933
# define OLIVE 0x808000
# define KHAKI 0xE519EFC
# define GREY 0x808080
# define LIGHTBLUE 0xADD8E6
# define BLUE 0x4169e1

# include "cub3d.h"

typedef struct s_data	t_data;
typedef struct s_cub	t_cub;
typedef struct s_cbd	t_cbd;

typedef struct s_ray
{
	float	pa;
	float	ra; //ray angle starting position
	float	rai; //ray angle iteration
	t_data	*mv;
	t_cub	*cub;
	t_cbd	*cbd;
}	t_ray;

// draw_image.c
void	draw_player(t_ray *ray);
void	draw_image(t_cbd *cbd, t_ray *ray);

// hooks.c
void	set_hooks(t_cbd *cbd);

// mlx_utils.c
void	my_mlx_pixel_put(t_cbd *cbd, int x, int y, int color);
int		destroy_flag(t_cbd *cbd, int flag);
int		destroy(t_cbd *cbd);

// ray_casting_utils.c
float	fix_angle(float a);
float	deg_to_rad(float a);
void	player_orientation_to_angle(t_data *mv, t_ray *ray);

// render.c
void	init_render_utils(t_cbd *cbd, t_data *mv, t_ray *ray);

//making_map.c
void	make_map(t_cbd *cbd, t_data *mv);

#endif
