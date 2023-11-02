/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:09:04 by yoonslee          #+#    #+#             */
/*   Updated: 2023/11/02 10:33:20 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CASTING_BONUS_H
# define RAY_CASTING_BONUS_H

# define FOV 60
# define MINI_PIX 16
# define GRID_PIX 64
# define TEX_PIX 64
# define K_ESC 53
# define ANGLE 5
# define SPEED 5
# define PLAYER_S 5
# define SENSITIVITY 0.05

# define BLACK 0x000000
# define WHITE 0xffffff
# define GREEN 0x009933
# define OLIVE 0x808000
# define KHAKI 0xE519EFC
# define GREY 0x808080
# define LIGHTBLUE 0xADD8E6
# define BLUE 0x4169e1
# define RED 0xFF0000
# define YELLOW 0xFFFF00
# define ORANGE 0xFFA500
# define PINK 0xFFC0CB
# define PURPLE 0x800080
# define CYAN 0x00FFFF
# define LAVENDER 0xE6E6FA
# define BROWN 0xA52A2A
# define MAGENTA 0xFF00FF
# define TEAL 0x008080

# include "cub3d.h"

typedef struct s_data		t_data;
typedef struct s_cub		t_cub;
typedef struct s_cbd		t_cbd;
typedef struct s_line		t_line;
typedef struct s_tex_img	t_tex_img;
typedef struct s_vector		t_vector;
typedef struct s_line		t_line;
typedef struct s_ray		t_ray;

// hooks_bonus.c
int				key_event(int keysym, t_ray *ray, t_cub *cub);
void			set_hooks(t_cbd *cbd, t_ray *ray, t_cub *cub);

//make_mini_map_bonus.c
void			draw_player(t_cbd *cbd, t_ray *ray);
void			make_mini_map(t_cbd *cbd, t_data *mv);

// minimap_ray_bonus.c
int				ft_abs(int a);
void			init_line(t_line *line, t_ray *ray);
void			bresenham(t_ray *ray, t_line *line, int color);
void			cast_rays(t_ray *ray);

//mouse_hooks_bonus.c
int				mouse_event(int x, int y, t_ray *ray);
int				mouse_press(int button, int x, int y, t_ray *ray);
int				mouse_release(int button, int x, int y, t_ray *ray);

// render_bonus.c
void			render_image_b(t_cbd *cbd, t_ray *ray);
void			init_ray_struct(t_ray *ray, t_data *data, t_cbd *cbd, \
t_line *line);
void			init_render_utils_b(t_cbd *cbd, t_data *mv, t_cub *cub);

//door_bonus.c
int				check_closable(t_ray *ray);
int				check_openable(t_ray *ray);

//drawing_bonus.c
void			draw_background(t_ray *ray);
void			draw_image_b(t_ray *ray, t_line *line, int door);
// void			color_wall(t_ray *ray, int pos, int wall);

// mlx_utils.c
void			my_mlx_pixel_put(t_cbd *cbd, int x, int y, int color);
unsigned int	my_mlx_pixel_get(t_tex_img *img, int x, int y);
int				mlx_exit_b(t_ray *ray, t_cub *cub, char *message, int flag);
int				mouse_exit(t_ray *ray);

//movement_bonus.c
int				movable(float x, float y, t_ray *ray);
void			move_frontback(t_ray *ray, char *direction);
void			move_sideway(t_ray *ray, char *direction);

// ray_casting_utils_bonus.c
int				is_wall_b(t_ray *ray, float x, float y);
float			fix_angle(float a);
float			deg_to_rad(float a);
void			player_orientation_to_angle(t_data *mv, t_ray *ray);
int				compare_draw_rays_b(t_ray *ray, t_line *line, int door);

//ray_casting.c
void			check_inits(t_ray *ray, t_line *line);
void			check_horizontal_gridline(t_ray *ray, t_line *line);
void			check_vertical_gridline(t_ray *ray, t_line *line);

//texture_bonus.c
void			texture_wall_b(t_ray *ray, int pos, int wall, int door);
void			texture_location(t_ray *ray, float y_count, float x, float y);

#endif
