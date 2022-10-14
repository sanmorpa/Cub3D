/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:57:42 by samoreno          #+#    #+#             */
/*   Updated: 2022/10/14 15:58:48 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	print_square(double x, double y, t_content info)
{
	double	tx;
	double	ty;

	ty = y;
	while (info.map.map[(int)ty] && ty <= y + 7)
	{
		tx = x;
		while (info.map.map[(int)ty][(int)tx] && tx <= x + 7)
		{
			if (info.map.map[(int)ty][(int)tx] == '1')
				mlx_pixel_put (info.mlx_ptr, info.win_ptr, (tx - x) * 20, (ty - y) * 20, RED);
			else if (info.map.map[(int)ty][(int)tx] != '0' && info.map.map[(int)ty][(int)tx] != ' ')
				mlx_pixel_put (info.mlx_ptr, info.win_ptr, (tx - x) * 20, (ty - y) * 20, GREY);
			tx = roundf((int)((tx + 0.05) * 100)) / 100;
		}
		ty = roundf((int)((ty + 0.05) * 100)) / 100;
	}
}

void	print_player(int x, int y, t_content info)
{
	int	aux_x;
	int	aux_y;

	if (info.player.x -3.5 < 0)
		x = info.player.x * MINI_TILE;
	if (info.player.y -3.5 < 0)
		y = info.player.y * MINI_TILE;
	mlx_pixel_put(info.mlx_ptr, info.win_ptr, x, y, BLUE);
	aux_x = x - 1;
	aux_y = y - 1;
	while (aux_x < x + 2)
		mlx_pixel_put(info.mlx_ptr, info.win_ptr, aux_x++, aux_y, BLUE);
	aux_y--;
	aux_x = x - 2;
	while (aux_x < x + 3)
		mlx_pixel_put(info.mlx_ptr, info.win_ptr, aux_x++, aux_y, BLUE);
	aux_y--;
	aux_x = x - 1;
	while (aux_x < x + 2)
		mlx_pixel_put(info.mlx_ptr, info.win_ptr, aux_x++, aux_y, BLUE);
	aux_y--;
	mlx_pixel_put(info.mlx_ptr, info.win_ptr, x, aux_y, BLUE);
}

void	print_minimap(t_content info)
{
	double	posx;
	double	posy;

	if (info.player.y -3.5 < 0)
		posy = 0;
	else
		posy = info.player.y - 3.5;
	if (info.player.x -3.5 < 0)
		posx = 0;
	else
		posx = info.player.x - 3.5;
	print_square(posx, posy, info);
	/*while (info.map.map[posy] && posy <= info.player.y + 3)
	{
		while (info.map.map[posy][posx] && posx <= info.player.x + 3)
		{
			if (info.map.map[posy][posx] == '1')
				print_square(mtile, mtile2, info, RED, 20, 20);
			else if (info.map.map[posy][posx] == 'O')
				print_square(mtile, mtile2, info, GREY, 20, 20);
			else if (info.map.map[posy][posx] == 'N' || info.map.map[posy][posx] == 'S'
				|| info.map.map[posy][posx] == 'W' || info.map.map[posy][posx] == 'E')
				print_square(mtile, mtile2, info, GREY, 20, 20);
			else
				print_square(mtile, mtile2, info, TRANS, 20, 20);
			posx++;
			mtile += MINI_TILE;
		}
		mtile = 0;
		mtile2 += MINI_TILE;
		posy++;
	}
	*/
	print_player(70, 70, info);
}
