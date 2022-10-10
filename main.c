/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 10:10:48 by samoreno          #+#    #+#             */
/*   Updated: 2022/10/10 15:56:02 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_leaks(void)
{
	system("leaks -q cub3D");
}

int	main(int argc, char **argv)
{
	t_content	info;

	info.player.ncordx = 0;
	info.player.ncordy = 0;
	errno = 0;
//	atexit(ft_check_leaks);
	if (input_errors(argc, argv) == 1)
		return (1);
	info.map = parse_map(argv[1]);
	if (info.map.x == -1 || !info.map.map)
		return (error_msg("Error: Invalid map format"));
	info.images = fill_images(&info);
	info.player = position_player(info.map.map);
	if (!info.mlx_ptr)
	{
		ft_free(info.map.map, info.map.y);
		free_infos(&info.map);
		return (1);
	}
	raycaster(info, -1);
//	print_minimap(info);
	mlx_hook(info.win_ptr, 17, 0, ft_red_cross, (void *)&info);
	mlx_hook(info.win_ptr, 2, 0, keypress, &info);
	mlx_hook(info.win_ptr, 3, 0, keyrelease, &info);
	mlx_loop_hook(info.mlx_ptr, movecharacter, &info);
	mlx_loop(info.mlx_ptr);
	ft_free(info.map.map, info.map.y);
	destroy_images(&info, &info.images);
	free_infos(&info.map);
	return (0);
}
