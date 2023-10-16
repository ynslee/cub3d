/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_to_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:57:39 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/16 10:22:47 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_validation.h"
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
/// @brief reads floor and ceiling color if there are spaces between rgb values (ex. F 25, 25, 25)
/// @param elem line splitted by spaces from file
/// @param cub
/// @return returns an array that contains the floor or ceiling color (ex. out[0] = F out[1] = 25,25,25)
char	**put_elems_str(char **elem, t_cub *cub)
{
	char	**out;
	char	*temp;
	int		len;

	len = ft_arrlen(elem);
	if (len > 4)
		file_print_error(cub, "Invalid colors for ceiling or floor!\n", 0);
	out = ft_calloc(3, sizeof(char *));
	if (!out)
		file_print_error(cub, "Could not allocate memory for RGB values!\n", 0);
	out[0] = ft_strdup(elem[0]);
	if (len == 3)
		out[1] = ft_strjoin(elem[1], elem[2]);
	else if (len == 4)
	{
		temp = ft_strjoin(elem[1], elem[2]);
		out[1] = ft_strjoin(temp, elem[3]);
		free(temp);
	}
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
	if (ft_arrlen(line_elem) > 2 && (!ft_strncmp_all(line_elem[0], "F") || \
		!ft_strncmp_all(line_elem[0], "C")))
		line_elem = put_elems_str(line_elem, cub);
	if (ft_strncmp_all(line_elem[0], "NO") == 0
		|| ft_strncmp_all(line_elem[0], "SO") == 0
		|| ft_strncmp_all(line_elem[0], "WE") == 0
		|| ft_strncmp_all(line_elem[0], "EA") == 0
		|| ft_strncmp_all(line_elem[0], "F") == 0
		|| ft_strncmp_all(line_elem[0], "C") == 0)
		put_elem_to_struct(line_elem, cub);
	cub->id_flag++;
	free(trim_line);
	free_char_array(line_elem);
}
