/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:54:20 by jhusso            #+#    #+#             */
/*   Updated: 2023/09/09 14:03:02 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_validation.h"

static void	parse_map(char *line, t_cub *cub)
{
	if (line)
	{
		if (!cub->map_str)
			cub->map_str = ft_strdup(line);
		else
			cub->map_str = ft_strjoin_gnl(cub->map_str, line);
	}
}

void	read_map(int fd, t_cub *cub)
{
	char	*line;

	while (42)
	{
		line = get_next_line(fd);
		if (ft_strncmp_all(line, "\n") != 0)
			break ;
	}
	while (42)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		else
			parse_map(line, cub);
	}
}
