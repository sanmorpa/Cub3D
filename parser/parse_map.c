/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:25:35 by samoreno          #+#    #+#             */
/*   Updated: 2022/10/03 12:40:30 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	fill_flood(char **map, int x, int y, int ret)
{
	if (y >= count_split(map) || y < 0)
		return (1);
	if (x >= (int)ft_strlen(map[y]) || x < 0)
		return (1);
	if (map[y][x] == 0)
		return (1);
	if (map[y][x] == '0' || map[y][x] == 'N'
		|| map[y][x] == 'S' | map[y][x] == 'E'
		|| map[y][x] == 'W')
	{
		if (map[y][x] == '0')
			map[y][x] = 'O';
		ret = fill_flood(map, x + 1, y, ret);
		ret = fill_flood(map, x - 1, y, ret);
		ret = fill_flood(map, x, y + 1, ret);
		ret = fill_flood(map, x, y - 1, ret);
	}
	return (ret);
}

static int	is_closed(t_map *map)
{
	int		coord[2];
	int		ret;

	coord[0] = 0;
	coord[1] = 0;
	initial_coordinates(coord, map->map);
	if (coord[0] == -1)
		return (1);
	ret = fill_flood(map->map, coord[0], coord[1], 0);
	return (ret);
}

int	check_map(t_map *map)
{
	int	i;
	int	j;
	int	player;

	i = -1;
	player = 0;
	map->x = (int)ft_strlen(map->map[0]);
	while (map->map[++i])
	{
		if ((int)ft_strlen(map->map[i]) > map->x)
			map->x = ft_strlen(map->map[i]);
		j = -1;
		while (map->map[i][++j])
		{
			if (map->map[i][j] != '1' && map->map[i][j] != '0'
				&& map->map[i][j] != 'N' && map->map[i][j] != 'S'
				&& map->map[i][j] != 'E' && map->map[i][j] != 'W'
				&& map->map[i][j] != ' ')
				return (1);
		}
	}
	if (is_closed(map) == 1)
		return (1);
	return (0);
}
