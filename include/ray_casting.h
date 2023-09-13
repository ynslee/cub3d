
#ifndef RAY_CASTING_H
# define RAY_CASTING_H

# include "cub3d.h"

typedef struct s_data	t_data;
typedef struct s_cub	t_cub;
typedef struct s_cbd	t_cbd;

typedef struct s_ray
{
	/* data */
	t_data	*mv;
	t_cub	*cub;
	t_cbd	*cbd;
}	t_ray;


// ray_casting_utils.c

#endif
