/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:31:12 by yoonslee          #+#    #+#             */
/*   Updated: 2023/09/06 12:31:14 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map_validation.h"

/**
 * @brief return the index of the last occurence if c in the string
 * returns -1 if can't find c
 */
int	ft_lastchr(char *str, char c)
{
	int	i;
	int	index;

	i = 0;
	index = -1;
	while (str[i])
	{
		if (str[i] == c)
			index = i;
		i++;
	}
	return (index);
}
