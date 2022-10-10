/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:06:49 by samoreno          #+#    #+#             */
/*   Updated: 2022/10/10 15:50:42 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	**reclean_map(char **old)
{
	char	**new;
	int		i;
	int		j;

	new = malloc(sizeof(char **) * (count_split(old) - 5));
	if (new)
	{
		i = 5;
		j = 0;
		while (old[++i])
		{
			new[j] = malloc(sizeof(char *) * (ft_strlen(old[i]) + 1));
			if (!new[j])
			{
				ft_free(new, j);
				new = NULL;
				break ;
			}
			ft_strlcpy(new[j], old[i], ft_strlen(old[i]) + 1);
			j++;
		}
		new[j] = 0;
	}
	ft_free(old, count_split(old));
	return (new);
}

static int	parser(t_map *map)
{
	init_null(map);
	if (parse_info(map) == 1)
		return (1);
	if (parse_fc(map->c, map->f) == 1)
	{
		free_infos(map);
		return (1);
	}
	map->map = reclean_map(map->map);
	if (!map->map)
		return (1);
	map->y = count_split(map->map);
	if (check_map(map) == 1)
		return (1);
	return (0);
}

t_map	parse_map(char *file)
{
	int		fd;
	t_map	map;

	map = count_lines(file);
	if (map.x == -1)
		return (map);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (map);
	map.map = fill_map(fd, &map);
	if (!map.map)
		return (map);
	close(fd);
	if (parser(&map) == 1)
	{
		ft_free(map.map, count_split(map.map));
		map.map = NULL;
		free_infos(&map);
	}
	return (map);
}

void	dir_vector(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->dirx = 0;
		player->diry = -1;
	}
	if (dir == 'S')
	{
		player->dirx = 0;
		player->diry = 1;
	}
	if (dir == 'E')
	{
		player->dirx = 1;
		player->diry = 0;
	}
	if (dir == 'W')
	{
		player->dirx = -1;
		player->diry = 0;
	}
	player->planex = player->diry * -0.66;
	player->planey = player->dirx * -0.66;
}

t_player	position_player(char **map)
{
	int			i;
	int			j;
	t_player	player;

	i = -1;
	player.keypressed = -1;
	player.rotpressed = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
			{
				player.x = j + 0.5;
				player.y = i + 0.5;
				dir_vector(&player, map[i][j]);
				return (player);
			}
		}
	}
	return (player);
}
