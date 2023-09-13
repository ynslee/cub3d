/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_last.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:26:28 by yoonslee          #+#    #+#             */
/*   Updated: 2023/09/13 12:29:29 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	is_set(char const c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim_last(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*trim;

	if (s1 == 0)
		return (0);
	i = 0;
	j = ft_strlen(s1);
	while (j > i && is_set(s1[j - 1], set))
		j --;
	trim = (char *)malloc(sizeof(char) * (j + 1));
	if (trim == 0)
		return (0);
	while (i < j)
	{
		trim[i] = s1[i];
		i++;
	}
	trim[i] = '\0';
	return (trim);
}
