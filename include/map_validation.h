/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:31:40 by yoonslee          #+#    #+#             */
/*   Updated: 2023/09/07 12:18:49 by yoonslee         ###   ########.fr       */
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

typedef struct s_data
{
	int		height;
	int		width;
	char	**map;
	char	**map_cpy;
	int		player_x;
	int		player_y;
}	t_data;

typedef struct s_cub	t_cub;

//basic_check.c
int		map_check(t_cub	*cub, t_data *mv);

//map_validation_utils.c
void	free_mv_struct(t_data *mv);
void	print_error(t_cub *cub, t_data *mv, char *str, int code);
void	copy_map(t_cub *cub, t_data *mv);
void	print_map(char **map);
void	flood_fill(t_data *mv, int x, int y, char c);

//index_utils.c
int		ft_lastchr(char *str, char c);
void	player_location(t_data *mv);
int		map_character_check(char c);
void	init_mv(t_data *mv);

#endif