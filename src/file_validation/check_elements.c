/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:13:30 by jhusso            #+#    #+#             */
/*   Updated: 2023/09/07 16:16:08 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_validation.h"

/*
Valid textures:
first info is the identifier
ends with .xpm
file exists, rights to open
all four files are different textures
have to find NO, SO, WE, EA first thing on the line
*/

void	check_textures(t_cub *cub)
{

}

void	check_required_elements(int fd, t_cub *cub)
{
	char	*line;

	while (42)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		else if (ft_strncmp_all(line, "\n") != 0 && cub->id_flag != 6
			&& !is_map(line))
			find_element(line, cub);
		else if (is_map(line) && cub->id_flag != 6)
			file_print_error(cub, "File does not have required elements!\n", 1);
		else if (ft_strncmp_all(line, "\n") != 0 && cub->id_flag == 6)
		{
			if (!cub->map_str)
				cub->map_str = ft_strdup(line);
			else
				cub->map_str = ft_strjoin_gnl(cub->map_str, line);
		}
		free(line);
	}
}
