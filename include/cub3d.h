
#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include "file_validation.h"
# include "../libft/libft.h"

typedef enum e_error
{
	SUCCESS,
	MALLOC_ERROR,
	MAP_INVALID
}	t_error;

typedef struct s_cub
{
	char *no;
	char *so;
	char *we;
	char *ea;
	char *f_color;
	char *c_color;
}	t_cub;

#endif
