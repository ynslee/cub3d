/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_to_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:57:39 by jhusso            #+#    #+#             */
/*   Updated: 2023/09/13 12:13:43 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_validation.h"

static void	put_elem_to_struct(char **element, t_cub *cub)
{
	if (check_elements(element, cub) == -1)
		file_print_error(cub, "Invalid texture file!\n", 0);
	else
	{
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
}

char	**put_elems_str(char **elem, t_cub *cub)
{
	char	**out;
	char	*temp;
	int		len;

	len = ft_arrlen(elem);
	if (len > 4)
		file_print_error(cub, "Invalid colors for ceiling or floor!\n", 0);
	out = ft_calloc(3, sizeof(char *));
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

void	find_element(char *line, t_cub *cub)
{
	char	**line_elem;
	char	*trim_line;

	trim_line = ft_strtrim(line, " \t\n");
	line_elem = ft_split(trim_line, ' ');
	if (ft_arrlen(line_elem) > 2 && (!ft_strncmp_all(line_elem[0], "F") || \
		!ft_strncmp_all(line_elem[0], "C")))
	{
		line_elem = put_elems_str(line_elem, cub);
	}
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
