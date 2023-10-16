/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:31:40 by yoonslee          #+#    #+#             */
/*   Updated: 2023/10/16 06:36:27 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_VALIDATION_H
# define MAP_VALIDATION_H

# include "cub3d.h"

// typedef enum
// {
// 	SUCCESS,
// 	MALLOC_ERROR,
// 	MAP_INVALID
// }

#define NO 0
#define SO 1
#define WE 2
#define EA 3

typedef struct s_cub	t_cub;
typedef struct s_ray	t_ray;
typedef struct s_cbd	t_cbd;

typedef struct s_tex_img
{
	void	*img_ptr;
	void	*img_addr;
	int		bpp;
	int		line_length;
	int		endian;
}			t_tex_img;

typedef struct s_data
{
	int				height;
	int				width;
	char			**map;
	char			**map_cpy;
	char			**buffer_cpy;
	int				player_x;
	int				player_y;
	char			player_view;
	unsigned int	floor_rgb;
	unsigned int	ceiling_rgb;
	t_tex_img		*texture[4];
	// void			*no_tex;
	// void			*so_tex;
	// void			*we_tex;
	// void			*ea_tex;
	int				img_width;
	int				img_height;
}	t_data;

//basic_check.c
int				map_check(t_cub	*cub, t_data *mv, t_cbd *cbd);

//map_validation_utils.c
void			free_mv_struct(t_data *mv);
void			print_error(t_cub *cub, t_data *mv, char *str, int code);
void			copy_map(t_cub *cub, t_data *mv);
void			print_map(char **map);
void			flood_fill(t_data *mv, int x, int y, char c);

//index_utils.c
int				ft_lastchr(char *str, char c);
void			player_location(t_data *mv);
int				map_character_check(char c);
void			init_mv(t_data *mv);

//fill_width.c
void			consecutive_new_lines(t_cub *cub, t_data *mv);
void			fill_width(t_data *mv);

//wall_check.c
void			set_buffer(t_cub *cub, t_data *data);
int				wall_check(t_cub *cub, t_data *data);

//rgb_colour.c
void			init_textures(t_cub *cub, t_cbd *cbd, t_data *data);
unsigned int	change_colour(char *colour);

#endif
