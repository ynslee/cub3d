/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:13:30 by jhusso            #+#    #+#             */
/*   Updated: 2023/09/07 17:15:11 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_validation.h"

/*
Valid textures:
ends with .xpm
file exists, rights to open
*/

int	check_textures(char *element)
{
	char	*ret;
	int		fd;

	printf("element in check textures = %s\n", element);
	ret = ft_strnstr(element, ".xpm", ft_strlen(element));
	if (ret == NULL)
		return (-1);
	// printf("ret = %s\n", ret);
	if (ft_strlen(ret) != 5)
	{
		// printf("coming here ret len = %zu\n", ft_strlen(ret));
		return (-1);
	}
	fd = open(element, O_RDONLY);
	printf("fd in check_textures = %i\n", fd);
	return (fd);
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
			file_print_error(cub, "File does not have required elements!\n");
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
