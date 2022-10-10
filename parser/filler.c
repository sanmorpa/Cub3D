/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 10:39:02 by samoreno          #+#    #+#             */
/*   Updated: 2022/10/05 10:10:00 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_map	count_lines(char *file)
{
	int		fd;
	t_map	map;
	char	*seen;

	map.x = -1;
	fd = open(file, O_RDONLY);
	if (fd >= 0)
	{
		seen = get_next_line(fd);
		if (seen)
		{
			map.x = ft_strlen(seen);
			map.y = 0;
			while (seen)
			{
				map.y++;
				if ((int)ft_strlen(seen) > map.x)
					map.x = ft_strlen(seen);
				free(seen);
				seen = get_next_line(fd);
			}
		}
		close(fd);
	}
	return (map);
}

static int	count_cleaned(char **prev)
{
	int	j;
	int	i;

	j = 0;
	i = -1;
	while (prev[++i])
	{
		if (prev[i][0] != 0)
			j++;
	}
	return (j);
}

static char	**clean_map(t_map *info, char **bf)
{
	char	**map;
	int		i[2];

	i[0] = -1;
	i[1] = 0;
	map = ft_calloc(sizeof(char *), (count_cleaned(bf) + 1));
	if (map)
	{
		while (bf[++i[0]])
		{
			if (bf[i[0]][0] != 0)
			{
				map[i[1]] = malloc(sizeof(char) * (ft_strlen(bf[i[0]]) + 1));
				if (!map[i[1]])
				{
					ft_free(map, i[1]);
					ft_free(bf, info->y);
					return (NULL);
				}
				ft_strlcpy(map[i[1]++], bf[i[0]], ft_strlen(bf[i[0]]) + 1);
			}
		}
	}
	ft_free(bf, info->y);
	return (map);
}

char	**fill_map(int fd, t_map *info)
{
	char	**map;
	int		i;

	map = malloc(sizeof(char **) * (info->y + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < info->y)
	{
		map[i] = get_next_line(fd);
		if (!map[i])
		{
			ft_free(map, i);
			return (NULL);
		}
		if (map[i][ft_strlen(map[i]) - 1] == '\n')
			map[i][ft_strlen(map[i]) - 1] = 0;
		i++;
	}
	map[i] = 0;
	map = clean_map(info, map);
	if (!map)
		return (NULL);
	info->y = count_cleaned(map);
	return (map);
}
