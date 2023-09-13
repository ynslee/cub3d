
#ifndef RAY_CASTING_H
# define RAY_CASTING_H

# define FOV 60

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


// ray_casting_utils.c
float	deg_to_rad(float a);
void	player_orientation_to_angle(t_data *mv, t_ray *ray);
void	init_render_utils(t_cbd *cbd, t_data *mv, t_ray *ray);

#endif
