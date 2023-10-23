/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:13:30 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/23 14:54:14 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/file_validation.h"

/// @brief checks that floor and ceiling colors have three numbers separated by comma
/// and that color values are correct
/// @param element rgb colorvalues separated by comma (second element of an array of splitted line)
/// @return 0 upon success, -1 if failure
static int	check_colors(t_cub *cub, char *element)
{
	char	**colors;
	int		i;

	colors = ft_split(element, ',');
	i = 0;
	while (i < 3)
	{
		if (colors[i][0] == '\n' || colors[i] == NULL \
			|| all_digits(colors[i]) == -1 || ft_arrlen(colors) != 3)
		{
			free_char_array(colors);
			return (-1);
		}
		if (ft_atoi(colors[i]) < 0 || ft_atoi(colors[i]) > 255)
			file_print_error(cub, "Invalid RGB value!\n", 0);
		else
			i++;
	}
	free_char_array(colors);
	return (0);
}

/// @brief checks validation of texture files
/// @param element path to file (second element of an array of splitted line)
/// @return returns -1 in case of failure, positive integer(fd) if succesfull
static int	check_textures(char *element)
{
	char	*ret;
	int		fd;

	ret = ft_strnstr(element, ".xpm", ft_strlen(element));
	if (ret == NULL)
		return (-1);
	if (ft_strlen(ret) != 4)
		return (-1);
	fd = open(element, O_RDONLY);
	close(fd);
	return (fd);
}

/// @brief Checks that the line that contains wall texture information in file is correct
/// @param element line from file splitted by spaces
/// @param cub
/// @return 0 if no problems
int	check_elements(char **element, t_cub *cub)
{
	if (!ft_strncmp_all(element[0], "NO") || !ft_strncmp_all(element[0], "SO")
		|| !ft_strncmp_all(element[0], "WE")
		|| !ft_strncmp_all(element[0], "EA"))
	{
		if (check_textures(element[1]) == -1)
			file_print_error(cub, "Invalid wall texture files!\n", 0);
		return (1);
	}
	else if (!ft_strncmp_all(element[0], "F")
		|| !ft_strncmp_all(element[0], "C"))
	{
		if (check_colors(cub, element[1]) == -1)
			file_print_error(cub, "Invalid colors for ceiling or floor!\n", 0);
		return (1);
	}
	return (0);
}
