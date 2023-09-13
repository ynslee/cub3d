/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:13:30 by jhusso            #+#    #+#             */
/*   Updated: 2023/09/12 12:12:32 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_validation.h"

static int	check_colors(char *element)
{
	char	**colors;
	char	*sub_color;
	int		i;

	sub_color = ft_substr(element, 0, ft_strlen(element) - 1);
	colors = ft_split(sub_color, ',');
	free(sub_color);
	i = 0;
	while (i < 3)
	{
		if (colors[i][0] == '\n' || colors[i] == NULL \
			|| all_digits(colors[i]) == -1 || ft_arrlen(colors) != 3)
			{
				free_char_array(colors);
				return (-1);
			}
		if (ft_atoi(colors[i]) >= 0 && ft_atoi(colors[i]) < 256)
			i++;
	}
	free_char_array(colors);
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
