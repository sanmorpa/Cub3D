/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 10:31:07 by samoreno          #+#    #+#             */
/*   Updated: 2022/10/05 10:41:06 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error_msg(char *msg)
{
	if (errno != 0)
	{
		perror("Error");
		errno = 0;
	}
	else
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
	return (1);
}

int	free_infos(t_map *map)
{
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->we)
		free(map->we);
	if (map->ea)
		free(map->ea);
	if (map->f)
		free(map->f);
	if (map->c)
		free(map->c);
	init_null(map);
	return (1);
}

void	ft_exit(t_content *info, int code, int error, char *msg)
{
	ft_free(info->map.map, info->map.y);
	destroy_images(info, &info->images);
	free_infos(&info->map);
	if (error == 1)
		error_msg(msg);
	if (code != 0)
		exit(code);
	if (error == 1)
		exit(1);
	exit(0);
}

int	input_errors(int argc, char**argv)
{
	int	i;

	if (argc != 2)
	{
		error_msg("Insert a single map");
		return (1);
	}
	i = ft_strlen(argv[1]);
	if (ft_strncmp(&argv[1][i - 4], ".cub", 5) != 0)
	{
		error_msg("Format must be map.cub");
		return (1);
	}
	return (0);
}

int	ft_red_cross(t_content *info)
{
	ft_free(info->map.map, info->map.y);
	destroy_images(info, &info->images);
	free_infos(&info->map);
	exit(0);
}
