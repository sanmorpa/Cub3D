/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:06:17 by samoreno          #+#    #+#             */
/*   Updated: 2022/10/10 14:53:01 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	count_path_no_spaces(char *line, char *type)
{
	int	i;
	int	commas;
	int	j;

	i = 0;
	j = 0;
	if (ft_strncmp(type, "C ", 3) != 0 && ft_strncmp(type, "F ", 3) != 0)
	{
		while (line[i] && line[i] != ' ')
			i++;
		return (i);
	}
	commas = 0;
	while (line[j])
	{
		if (line[j] == ',')
			commas++;
		if (ft_isdigit(line[j]) == 1 || line[j] == ',' || line[j] == '-' || (line[j] == ' ' && commas <= 2))
			i++;
		j++;
	}
	return (i);
}

static void	copy_path_no_spaces(char *dst, char *src, char *type)
{
	size_t	i;
	size_t	j;
	int		commas;

	i = 0;
	j = 0;
	if (ft_strncmp(type, "C ", 3) != 0 && ft_strncmp(type, "F ", 3) != 0)
	{
		while (src[i] && src[i] != ' ')
		{
			dst[i] = src[i];
			i++;
		}
	}
	else
	{
		commas = 0;
		while (src[j])
		{
			if (src[j] == ',')
				commas++;
			if (src[j] != ' ' || (src[j] == ' ' && commas <= 2))
				dst[i++] = src[j++];
			else
				j++;
		}
	}
	dst[i] = 0;
}

static char	*save_path(char *line, char *type)
{
	int		i;
	int		j;
	char	*info;

	i = 0;
	j = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (ft_strncmp(&line[i], type, ft_strlen(type)) != 0)
		return (NULL);
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i])
		return (NULL);
	info = malloc(sizeof(char) * (count_path_no_spaces(&line[i], type) + 1));
	if (info)
		copy_path_no_spaces(info, &line[i], type);
	return (info);
}

int	parse_info(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (++i < 6)
	{
		while (map->map[i][j] == ' ')
			j++;
		if (map->map[i][j] == 'N')
			map->no = save_path(map->map[i], "NO ");
		if (map->map[i][j] == 'S')
			map->so = save_path(map->map[i], "SO ");
		if (map->map[i][j] == 'W')
			map->we = save_path(map->map[i], "WE ");
		if (map->map[i][j] == 'E')
			map->ea = save_path(map->map[i], "EA ");
		if (map->map[i][j] == 'F')
			map->f = save_path(map->map[i], "F ");
		if (map->map[i][j] == 'C')
			map->c = save_path(map->map[i], "C ");
	}
	if (!map->no || !map->so || !map->we || !map->ea || !map->f || !map->c)
		return (free_infos(map));
	return (0);
}
