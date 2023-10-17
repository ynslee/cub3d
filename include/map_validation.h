/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:31:40 by yoonslee          #+#    #+#             */
/*   Updated: 2023/10/17 15:41:19 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_VALIDATION_H
# define MAP_VALIDATION_H

# include "cub3d.h"

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
	int		width;
	int		height;
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
	int				img_width;
	int				img_height;
}	t_data;

//basic_check.c
int				map_check(t_cub	*cub, t_data *mv);

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
char			*fill_row(t_data *mv, char **map, char *temp, int i);
void			consecutive_new_lines(t_cub *cub, t_data *mv);
void			fill_width(t_data *mv);

//wall_check.c
void			set_buffer(t_cub *cub, t_data *data);
int				wall_check(t_cub *cub, t_data *data);

//rgb_colour.c
void			init_textures(t_cub *cub, t_cbd *cbd, t_data *data);
unsigned int	change_colour(char *colour);

#endif
