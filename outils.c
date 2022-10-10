/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:31:50 by samoreno          #+#    #+#             */
/*   Updated: 2022/10/10 12:00:10 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

void	initial_coordinates(int *coord, char **map)
{
	int	i;
	int	j;
	int	player;

	i = -1;
	player = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				coord[0] = j;
				coord[1] = i;
				player++;
			}
		}
	}
	if (player != 1)
		coord[0] = -1;
}

void	init_null(t_map *map)
{
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->f = NULL;
	map->c = NULL;
}

unsigned long	rgba_to_hex(int r, int g, int b, int a)
{
	unsigned long	hex;

	hex = ((a & 0xff) << 24) + ((r & 0xff) << 16) + ((g & 0xff) << 8)
		+ (b & 0xff);
	return (hex);
}
