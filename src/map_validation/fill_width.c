/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_width.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:05:53 by yoonslee          #+#    #+#             */
/*   Updated: 2023/09/08 11:11:33 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map_validation.h"
#include "../../include/cub3d.h"

char	*fill_temp(t_data *mv, char *temp, int i)
{
	int	j;

	j = -1;
	while (mv->map_cpy[i][++j])
		temp[j] = mv->map_cpy[i][j];
	while (j < mv->width)
	{
		temp[j] = 'X';
		j++;
	}
	temp[j] = '\0';
	return (temp);
}

void	fill_width(t_data *mv)
{
	int		i;
	char	*temp;
	int		len;

	i = 0;
	while (mv->map_cpy[i])
	{
		if ((int)ft_strlen(mv->map_cpy[i]) < mv->width)
		{
			len = mv->width - (int)ft_strlen(mv->map_cpy[i]);
			temp = ft_calloc(mv->width + 1, sizeof(char));
			temp = fill_temp(mv, temp, i);
			free(mv->map_cpy[i]);
			mv->map_cpy[i] = ft_strdup(temp);
			free(temp);
		}
		i++;
	}
	print_map(mv->map_cpy);
}
