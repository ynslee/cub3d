/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:23:29 by yoonslee          #+#    #+#             */
/*   Updated: 2023/09/13 11:25:57 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_char_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_printf("str[%d] is :%s\n", i, str[i]);
		i++;
	}
}
