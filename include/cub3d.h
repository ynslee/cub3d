/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:40:08 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/25 09:59:59 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "file_validation.h"
# include "map_validation.h"
# include "ray_casting.h"
# include "ray_casting_bonus.h"
# include "../libft/libft.h"

# define WIN_SIZE_X 1920
# define WIN_SIZE_Y 1080

# define NO 0
# define SO 1
# define WE 2
# define EA 3

typedef struct s_cbd
{
	void	*mlx;
	void	*window;
	void	*img;
	void	*wall;
	void	*background;
	int		img_len;
	char	*img_addr;
	int		img_bpp;
	int		endian;
}	t_cbd;

typedef struct s_cub
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*f_color;
	char			*c_color;
	char			*map_str;
	int				id_flag;
}					t_cub;

void	print_struct(t_cub *cub);
void	free_cub_struct(t_cub *cub);

#endif
