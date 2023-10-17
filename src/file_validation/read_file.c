/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:55:44 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/17 12:20:44 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_validation.h"

/// @brief Check if the map file is empty, or if there is no map
/// @param cub
/// @param line
/// @param line_flag counts the element lines in map file
static void	check_empty_file(t_cub *cub, char *line, int line_flag)
{
	if (!line && line_flag == 0)
		file_print_error(cub, "File empty!\n", 0);
	if (!cub->map_str || cub->map_str[0] == '\0')
		file_print_error(cub, "No map in file!\n", 1);
}

/// @brief Checks if given map file name ends with '.cub'
/// @param file_name argv[1]
/// @return fd if file name is valid and open() is successful, returns -1 if any error occures
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

/// @brief reads the map line by line with get_next_line and saves in to string to cub struct
/// @param fd
/// @param cub
static void	read_map(int fd, t_cub *cub)
{
	char	*line;
	char	*map_str;
	char	*temp;

	map_str = NULL;
	while (42)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (cub->id_flag == 6 && !is_map(line) && ft_strncmp_all(line, "\n") != 0)
			file_print_error(cub, "Duplicate elements!\n", 1);
		if (!map_str)
			map_str = ft_strdup(line);
		else
			map_str = ft_strjoin_gnl(map_str, line);
		free(line);
	}
	temp = ft_strtrim(map_str, "\n");
	cub->map_str = ft_strtrim_last(temp, " \n");
	free(temp);
	free (map_str);
	free (line);
}
/// @brief reads file one line at a time, and checks that all the required elements are found
/// in right order
/// @param fd
/// @param cub
void	read_file(int fd, t_cub *cub)
{
	char	*line;
	int		line_flag;

	line_flag = 0;
	while (cub->id_flag != 6)
	{
		line = get_next_line(fd);
		if (line == NULL)
			file_print_error(cub, "Error in get_next_line!\n", 1);
		if (line && cub->id_flag == 6 && !is_map(line))
			file_print_error(cub, "Texture file duplicates!\n", 1);
		else if (!line || cub->id_flag == 6)
			break ;
		else if (ft_strncmp_all(line, "\n") != 0 && cub->id_flag != 6
			&& !is_map(line))
			find_element(line, cub);
		else if (is_map(line) && cub->id_flag != 6)
			file_print_error(cub, "File does not have required elements!\n", 1);
		free(line);
	}
	read_map(fd, cub);
	line_flag = 1;
	check_empty_file(cub, line, line_flag);
}
