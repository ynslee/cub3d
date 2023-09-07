# ifndef FILE_VALIDATION_H
#define FILE_VALIDATION_H

#include "cub3d.h"

typedef struct s_cub t_cub;

// elements_to_struct.c
int		valid_elements(int fd, t_cub *cub);
int		valid_file(char *file_name);

// check_textures.c

//file_validation_utils.c
int	is_map(char *line);



#endif
