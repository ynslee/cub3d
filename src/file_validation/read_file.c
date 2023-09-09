/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:55:44 by jhusso            #+#    #+#             */
/*   Updated: 2023/09/09 13:58:55 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_validation.h"

void	check_empty_file(t_cub *cub, char *line, int line_flag)
{
	if (!line && line_flag == 0)
		file_print_error(cub, "File empty!\n", 0);
	if (!cub->map_str)
		file_print_error(cub, "No map in file!\n", 1);
}

int	valid_file(char *file_name)
{
	char	*ret;
	int		fd;

	ret = ft_strnstr(file_name, ".cub", ft_strlen(file_name));
	if (ret == NULL)
		return (-1);
	if (ft_strlen(ret) != 4)
		return (-1);
	fd = open(file_name, O_RDONLY);
	return (fd);
}

void	read_file(int fd, t_cub *cub)
{
	char	*line;
	int		line_flag;

	line_flag = 0;
	while (42)
	{
		line = get_next_line(fd);
		if (!line || cub->id_flag == 6)
			break ;
		else if (ft_strncmp_all(line, "\n") != 0 && cub->id_flag != 6
			&& !is_map(line))
			find_element(line, cub);
		else if (is_map(line) && cub->id_flag != 6)
			file_print_error(cub, "File does not have required elements!\n", 0);
	}
	read_map(fd, cub);
	line_flag = 1;
	free(line);
	check_empty_file(cub, line, line_flag);
}
