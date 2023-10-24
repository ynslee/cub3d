/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:09:04 by yoonslee          #+#    #+#             */
/*   Updated: 2023/10/24 12:43:46 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CASTING_H
# define RAY_CASTING_H

# define FOV 60
# define MINI_PIX 16
# define GRID_PIX 64
# define TEX_PIX 64
# define K_ESC 53
# define ANGLE 5
# define SPEED 5
# define PLAYER_S 5
# define PR_PLANE 1662
# define SENSITIVITY 0.05
// # define NOSE_LEN 1

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
# include "map_validation.h"

typedef struct s_data		t_data;
typedef struct s_cub		t_cub;
typedef struct s_cbd		t_cbd;
typedef struct s_line		t_line;
typedef struct s_tex_img	t_tex_img;

typedef struct s_vector
{
	float	x;
	float	y;
	float	pa;
}	t_vector;

/**
 * @param x0 line starting x position
 * @param y0 line starting y position
 * @param x1 line ending x
 * @param y1 line ending y
 * @param dx absolute difference between x0 and x1
 * @param dy absolute difference between y0 and y1
 * @param sx sign of x -> sx = 1 if x1 > x0 | sx = -1 if x1 < x0
 * @param sy sign of y -> sy = 1 if y1 > y0 | sy = -1 if y1 < y0
*/
typedef struct s_line
{
	float	x0;
	float	y0;
	float	x1;
	float	y1;
	float	xa;
	float	ya;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		error;
	int		error2;
	float	v_x1;
	float	v_y1;
	float	v_xa;
	float	v_ya;
	float	rx;
	float	ry;
}	t_line;

/**
 * @param pa angle of the player Degrees
 * @param ra ray angle starting position (pa + FOV / 2),
 * rays are casted from player right to left
 * @param rai ray angle iteration
//  * @param cotan line length(cotan)
 * @param center_x center of the window_width
 * @param center_y center of the window_height
//  * @param xo x's offset
//  * @param yo y's offset
 * @param pdx position delta x, delta represents a change
 * in variable
 * @param pdy position delta y
 * @param r_cos rays cos incrementation
 * @param r_sin rays sin incrementation
 * @param pix_x_pos player's x position in pixel
 * @param pix_y_pos player's y position in pixel
 */
typedef struct s_ray
{
	float			pa;
	float			ra;
	int				dof;
	float			d_tan;
	float			xa;
	float			ya;
	float			ray_count;
	float			center_width;
	float			center_height;
	float			pix_x_pos;
	float			pix_y_pos;
	float			pdx;
	float			pdy;
	float			r_end_x;
	float			r_end_y;
	char			shortest;
	float			distance;
	float			wall_height;
	float			tex_x;
	float			tex_y;
	float			mou_x;
	int				dragging;
	void			*texture;
	struct s_data	*data;
	struct s_cbd	*cbd;
	struct s_vector	*vector;
	struct s_line	*line;
}	t_ray;

//draw_utils.c
int				set_wall_direction(t_ray *ray);

//drawing.c
void			draw_background(t_ray *ray);
void			draw_image(t_ray *ray, t_line *line);
// void			color_wall(t_ray *ray, int pos, int wall);

// hooks.c
int				key_event(int keysym, t_ray *ray, t_cub *cub);
void			set_hooks(t_cbd *cbd, t_ray *ray, t_cub *cub);

//make_mini_map.c
// void			draw_player(t_cbd *cbd, t_ray *ray);
// void			make_mini_map(t_cbd *cbd, t_data *mv);

// minimap_ray.c
// int				ft_abs(int a);
// void			init_line(t_line *line, t_ray *ray);
// void			bresenham(t_ray *ray, t_line *line, int color);
// void			cast_rays(t_ray *ray);

// mlx_utils.c
void			my_mlx_pixel_put(t_cbd *cbd, int x, int y, int color);
unsigned int	my_mlx_pixel_get(t_tex_img *img, int x, int y);
int				mlx_exit(t_ray *ray, t_cub *cub, char *message, int flag);
// int				destroy(t_cbd *cbd);

//mouse_hooks.c
int				mouse_event(int x, int y, t_ray *ray);
int				mouse_press(int button, int x, int y, t_ray *ray);
int				mouse_release(int button, int x, int y, t_ray *ray);

//movement.c
int				movable(float x, float y, t_ray *ray);
void			move_frontback(t_ray *ray, char *direction);
void			move_sideway(t_ray *ray, char *direction);

// ray_casting_utils.c
int				is_wall(t_ray *ray, float x, float y);
float			fix_angle(float a);
float			deg_to_rad(float a);
void			player_orientation_to_angle(t_data *mv, t_ray *ray);
void			compare_draw_rays(t_ray *ray, t_line *line);

//ray_casting.c
void			check_inits(t_ray *ray, t_line *line);
void			check_horizontal_gridline(t_ray *ray, t_line *line);
void			check_vertical_gridline(t_ray *ray, t_line *line);

// render.c
void			render_image(t_cbd *cbd, t_ray *ray, t_data *mv);
void			init_ray_struct(t_ray *ray, t_data *data, t_cbd *cbd, \
t_line *line);
void			init_render_utils(t_cbd *cbd, t_data *mv, t_cub *cub);

//texture.c
void			texture_wall(t_ray *ray, int pos, int wall, float y_count);
void			texture_location(t_ray *ray, float y_count, float x, float y);

#endif
