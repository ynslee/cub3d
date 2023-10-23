/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_to_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:57:39 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/23 14:32:09 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/file_validation.h"
/// @brief first checks that element information is valid, then adds the
/// information to cub struct, gives error message if finds duplicate elements
/// @param element line from file splitted by spaces
/// @param cub
static void	put_elem_to_struct(char **element, t_cub *cub)
{
	check_elements(element, cub);
	if (ft_strncmp_all(element[0], "NO") == 0 && !cub->no)
		cub->no = ft_strdup(element[1]);
	else if (ft_strncmp_all(element[0], "SO") == 0 && !cub->so)
		cub->so = ft_strdup(element[1]);
	else if (ft_strncmp_all(element[0], "WE") == 0 && !cub->we)
		cub->we = ft_strdup(element[1]);
	else if (ft_strncmp_all(element[0], "EA") == 0 && !cub->ea)
		cub->ea = ft_strdup(element[1]);
	else if (ft_strncmp_all(element[0], "F") == 0 && !cub->f_color)
		cub->f_color = ft_strdup(element[1]);
	else if (ft_strncmp_all(element[0], "C") == 0 && !cub->c_color)
		cub->c_color = ft_strdup(element[1]);
	else
		file_print_error(cub, "Texture file duplicates!\n", 1);
}

/// @brief reads floor and ceiling color if there are spaces between rgb
/// values (ex. F 25, 25, 25)
/// @param elem line splitted by spaces from file
/// @param cub
/// @return returns an array that contains the floor or ceiling color
/// (ex. out[0] = F out[1] = 25,25,25)
static char	**put_elems_str(char **elem, t_cub *cub)
{
	char	**out;
	int		len;

	len = ft_arrlen(elem);
	if (len > 2)
		file_print_error(cub, "Invalid colors for ceiling or floor!\n", 0);
	multiple_commas(cub, elem[1]);
	out = ft_calloc(3, sizeof(char *));
	if (!out)
		file_print_error(cub, "Could not allocate memory for RGB values!\n", 0);
	out[0] = ft_strdup(elem[0]);
	out[1] = ft_strdup(elem[1]);
	printf("out[0] %s\n", out[0]);
	printf("out[1] %s\n", out[1]);
	free_char_array(elem);
	return (out);
}

/// @brief searches for lines in file that describe wall textures and
/// floor and ceilin colors
/// @param line line read from file with get__next_line
/// @param cub
void	find_element(char *line, t_cub *cub)
{
	char	**line_elem;
	char	*trim_line;

	trim_line = ft_strtrim(line, " \t\n");
	line_elem = ft_split(trim_line, ' ');
	if ((!ft_strncmp_all(line_elem[0], "F") || \
		!ft_strncmp_all(line_elem[0], "C"))) // ft_arrlen(line_elem) > 2 &&
		{
			printf("going in with line %s\n", trim_line);
			line_elem = put_elems_str(line_elem, cub);
		}
	else if (ft_strncmp_all(line_elem[0], "NO") == 0
		|| ft_strncmp_all(line_elem[0], "SO") == 0
		|| ft_strncmp_all(line_elem[0], "WE") == 0
		|| ft_strncmp_all(line_elem[0], "EA") == 0
		|| ft_strncmp_all(line_elem[0], "F") == 0
		|| ft_strncmp_all(line_elem[0], "C") == 0)
		put_elem_to_struct(line_elem, cub);
	else
		file_print_error(cub, "Invalid element!\n", 0);
	cub->id_flag++;
	free(trim_line);
	free_char_array(line_elem);
}
