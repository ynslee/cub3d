/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:04:28 by yoonslee          #+#    #+#             */
/*   Updated: 2023/10/26 11:18:26 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map_validation.h"

/**
 * @brief free mv_struct
 */
void	free_mv_struct_b(t_data *mv)
{
	int	i;

	if (mv->map)
		free_char_array(mv->map);
	if (mv->map_cpy)
		free_char_array(mv->map_cpy);
	if (mv->buffer_cpy)
		free_char_array(mv->buffer_cpy);
	i = 0;
	while (i < 4)
	{
		if (mv->textures[i])
		{
			free (mv->textures[i]);
			mv->textures[i] = NULL;
		}
		i++;
	}
}

/// @brief print the error message, frees struct if its already allocated and
/// exits
/// @param cub
/// @param mv
/// @param str error message
/// @param code flag if struct needs to be freed
void	print_error_b(t_cub *cub, t_data *mv, char *str, int code)
{
	ft_putstr_fd(str, 2);
	if (code == 1)
		free_cub_struct(cub);
	if (code == 2)
	{
		free_mv_struct_b(mv);
	}
	exit(1);
}
