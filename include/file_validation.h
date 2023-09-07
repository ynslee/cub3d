/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:08:23 by jhusso            #+#    #+#             */
/*   Updated: 2023/09/07 17:01:34 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_VALIDATION_H
# define FILE_VALIDATION_H

# include "cub3d.h"

typedef struct s_cub	t_cub;

// elements_to_struct.c
void	find_element(char *line, t_cub *cub);
int		valid_elements(int fd, t_cub *cub);
int		valid_file(char *file_name);

// check_elements.c
int		check_textures(char *element);
void	check_required_elements(int fd, t_cub *cub);

//file_validation_utils.c
void	file_print_error(t_cub *cub, char *str);
int		is_map(char *line);

#endif
