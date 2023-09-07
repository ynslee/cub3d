# ifndef FILE_VALIDATION_H
#define FILE_VALIDATION_H

#include "cub3d.h"

typedef struct s_cub t_cub;

// check_textures.c
void	put_elem_to_struct(char **element, t_cub *cub);
int		check_line(char *line, t_cub *cub);
int		valid_elements(int fd, t_cub *cub);
int		valid_file(char *file_name);

#endif
