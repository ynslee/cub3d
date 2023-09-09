/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:08:23 by jhusso            #+#    #+#             */
/*   Updated: 2023/09/09 14:02:35 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_VALIDATION_H
# define FILE_VALIDATION_H

# include "cub3d.h"

typedef struct s_cub	t_cub;

// elements_to_struct.c
void	find_element(char *line, t_cub *cub);
int		valid_elements(int fd, t_cub *cub);

// check_elements.c
int		check_elements(char **element, t_cub *cub);

//file_validation_utils.c
int		all_digits(char *number);
void	file_print_error(t_cub *cub, char *str, int struct_flag);
int		is_map(char *line);

//read_file.c
void	check_empty_file(t_cub *cub, char *line, int line_flag);
int		valid_file(char *file_name);
void	read_file(int fd, t_cub *cub);

//read_map.c
void	read_map(int fd, t_cub *cub);

#endif
