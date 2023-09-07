
#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "file_validation.h"
# include "map_validation.h"
# include "../libft/libft.h"

typedef struct s_cbd
{
	void	*mlx;
	void	*window;
	void	*background;
	int		img_len;
}	t_cbd;


#endif
