/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:13:30 by jhusso            #+#    #+#             */
/*   Updated: 2023/09/08 17:10:15 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_validation.h"

static int	all_digits(char *number)
{
	int	i;
	int	len;

	len = ft_strlen(number);
	i = -1;
	while (++i < len)
	{
		if (!ft_isdigit(number[i]))
			return (-1);
	}
	return (0);
}

/// free
static int	check_colors(char *element)
{
	char	**colors;
	char	*sub_color;
	int		i;

	sub_color = ft_substr(element, 0, ft_strlen(element) - 1);
	colors = ft_split(sub_color, ',');
	if (ft_arrlen(colors) != 3)
		return (-1);
	i = 0;
	while (i < 3)
	{
		if (colors[i][0] == '\n' || colors[i] == NULL)
			return (-1);
		if (all_digits(colors[i]) == -1)
			return (-1);
		if (ft_atoi(colors[i]) >= 0 && ft_atoi(colors[i]) < 256)
			i++;
		else
			return (-1);
	}
	return (0);
}

/// @brief checks validation of texture files
/// @param element path to file
/// @return returns -1 in case of failure, positive integer(fd) if succesfull
static int	check_textures(char *element)
{
	char	*ret;
	int		fd;
	char	*sub_elem;

	// printf("element in check textures = %s\n", element);
	ret = ft_strnstr(element, ".xpm", ft_strlen(element));
	if (ret == NULL)
		return (-1);
	if (ft_strlen(ret) != 5)
		return (-1);
	sub_elem = ft_substr(element, 0, ft_strlen(element) - 1);
	fd = open(sub_elem, O_RDONLY);
	free(sub_elem);
	return (fd);
}

int	check_elements(char **element, t_cub *cub)
{
	if (!ft_strncmp_all(element[0], "NO") || !ft_strncmp_all(element[0], "SO")
		|| !ft_strncmp_all(element[0], "WE")
		|| !ft_strncmp_all(element[0], "EA"))
	{
		if (check_textures(element[1]) == -1)
			file_print_error(cub, "invalid wall texture files!\n", 0);
	}
	else if (!ft_strncmp_all(element[0], "F")
		|| !ft_strncmp_all(element[0], "C"))
	{
		if (check_colors(element[1]) == -1)
			file_print_error(cub, "Invalid colors for ceiling or floor!\n", 0);
	}
	return (0);
}

void	check_empty_file(t_cub *cub, char *line, int line_flag)
{
	if (!line && line_flag == 0)
		file_print_error(cub, "File empty!\n", 0);
	 if (!cub->map_str)
	 	file_print_error(cub, "No map in file!\n", 1);
}

void	check_required_elements(int fd, t_cub *cub)
{
	char	*line;
	int		line_flag;

	line_flag = 0;
	while (42)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		else if (ft_strncmp_all(line, "\n") != 0 && cub->id_flag != 6
			&& !is_map(line))
			find_element(line, cub);
		else if (is_map(line) && cub->id_flag != 6)
			file_print_error(cub, "File does not have required elements!\n", 0);
		else if (cub->id_flag == 6) //ft_strncmp_all(line, "\n") != 0 &&
		{
			if (!cub->map_str)
				cub->map_str = ft_strdup(line);
			else
				cub->map_str = ft_strjoin_gnl(cub->map_str, line);
		}
		line_flag = 1;
		free(line);
	}
	check_empty_file(cub, line, line_flag);
}
