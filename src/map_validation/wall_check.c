/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 07:51:46 by jhusso            #+#    #+#             */
/*   Updated: 2023/09/11 08:15:56 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
- free map cpy and set to null
- make map cpy again
- set the buffer
- flood fill to check walls are closed

*/

void	set_buffer(t_data *data)
{
	map_cpy = ft_calloc(data->height + 2, sizeof(char*));
}

int	wall_check(t_data *data)
{
	set_buffer(data);
}
