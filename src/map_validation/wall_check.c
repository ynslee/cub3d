/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 07:51:46 by jhusso            #+#    #+#             */
/*   Updated: 2023/09/11 10:57:41 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
- free map cpy and set to null
- make map cpy again
- set the buffer
- flood fill to check walls are closed

*/

static void	ft_bx(void *s, size_t n)
{
	char	*ptr;
	size_t	i;

	ptr = (char *)s;
	i = 0;
	while (i < n)
		ptr[i++] = 'X';
}

void	set_buffer(t_data *data)
{
	char	**buffer_cpy;
	int		i;
	int		j;

	i = -1;
	buffer_cpy = ft_calloc(data->height + 3, sizeof(char *));
	while (++i < data->height + 2)
		buffer_cpy[i] = ft_calloc(data->width + 3, sizeof(char *));
	ft_bx(buffer_cpy[0], data->width + 2);
	i = 1;
	j = 0;
	while (i < data->height - 1)
	{
		buffer_cpy[i] = ft_strjoin("X", data->map[j]);
		buffer_cpy[i] = ft_strjoin(buffer_cpy[i], "X");
		i++;
		j++;
	}
	printf("%i\n", i);
	ft_bx(buffer_cpy[i], data->width + 2);
	print_map(buffer_cpy);
}

int	wall_check(t_data *data)
{
	set_buffer(data);
	return (0);
}
