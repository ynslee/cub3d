/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:08:23 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/25 10:01:39 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_VALIDATION_H
# define FILE_VALIDATION_H

# include "cub3d.h"

typedef struct s_cub	t_cub;

// check_elements.c
int		check_elements(char **element, t_cub *cub);

// elements_to_struct.c
void	find_element(char *line, t_cub *cub);

//file_validation_utils.c
void	multiple_commas(t_cub *cub, char *rgb_values);
int		all_digits(char *number);
void	file_print_error(t_cub *cub, char *str, int struct_flag);
int		is_map(char *line);

//read_file.c
int		valid_file(char *file_name);
void	read_file(int fd, t_cub *cub);

#endif
