/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:01:42 by jhusso            #+#    #+#             */
/*   Updated: 2023/09/07 16:01:44 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_validation.h"

void	file_print_error(t_cub *cub, char *str, int line_flag)
{
	ft_putstr_fd(str, 2);
	if (line_flag == 1)
		free_struct(cub);
	exit(1);
}

int	is_map(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_isdigit(line[i]))
		return (1); //if is map
	return (0); //if its not map
}
