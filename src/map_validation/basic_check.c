/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:54:22 by yoonslee          #+#    #+#             */
/*   Updated: 2023/09/05 13:33:32 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// First check of the map
//  Is there a player? or multiple players (also if map only ones, it would be caught here)
//  is there invalid character
//  more than 2 consecutive '\n'
// If there is two different maps?
//  Changing the wall element with floodfill algo -> if there is two maps, invalid -> if player is inside wall, invalid?

#include "cub3d.h"

// char	**copy_map(char *map)
// {
	
// }

int	map_check(char *map)
{
	char	**map_cpy;


	map_cpy = copy_map(map);
}
