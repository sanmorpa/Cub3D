/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:57:42 by samoreno          #+#    #+#             */
/*   Updated: 2022/10/05 13:06:35 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	print_square(int x, int y, t_content info, int color)
{
	int	i;
	int	j;

	i = y;
	while (i < (y + MINI_TILE))
	{
		j = x;
		while (j < (x + MINI_TILE))
		{
			mlx_pixel_put (info.mlx_ptr, info.win_ptr, j, i, color);
			j++;
		}
		i++;
	}
}

void	print_player(int x, int y, t_content info)
{
	int	aux_x;
	int	aux_y;

	mlx_pixel_put(info.mlx_ptr, info.win_ptr, x, y, ORANGE);
	aux_x = x - 1;
	aux_y = y - 1;
	while (aux_x < x + 2)
		mlx_pixel_put(info.mlx_ptr, info.win_ptr, aux_x++, aux_y, ORANGE);
	aux_y--;
	aux_x = x - 2;
	while (aux_x < x + 3)
		mlx_pixel_put(info.mlx_ptr, info.win_ptr, aux_x++, aux_y, ORANGE);
	aux_y--;
	aux_x = x - 1;
	while (aux_x < x + 2)
		mlx_pixel_put(info.mlx_ptr, info.win_ptr, aux_x++, aux_y, ORANGE);
	aux_y--;
	mlx_pixel_put(info.mlx_ptr, info.win_ptr, x, aux_y, ORANGE);
}

void	print_minimap(t_content info)
{
	int	i;
	int	j;
	int posx;
	int posy;

	posx = 0;
	posy = 0;
	i = -1;
	while (info.map.map[++i])
	{
		j = -1;
		while (info.map.map[i][++j])
		{
			if (((info.player.x - j) < 3 && (info.player.x - j) > -3) && (info.player.y - i) < 3 && (info.player.y - i) > -3)
			{
				if (posx == 0)
					posx = i - 1;
				if (posy == 0)
					posy = j - 1;
				if (info.map.map[i][j] == '1')
					print_square((j - posy) * MINI_TILE, (i - posx) * MINI_TILE, info, RED);
				else if (info.map.map[i][j] == 'O')
					print_square((j - posy) * MINI_TILE, (i - posx) * MINI_TILE, info, GREY);
				else if (info.map.map[i][j] == 'N' || info.map.map[i][j] == 'S'
					|| info.map.map[i][j] == 'W' || info.map.map[i][j] == 'E')
					print_square((j - posy) * MINI_TILE, (i - posx) * MINI_TILE, info, GREY);
				else
					print_square((j - posy) * MINI_TILE, (i - posx) * MINI_TILE, info, TRANS);
				print_player(info.player.x * MINI_TILE, info.player.y
					* MINI_TILE, info);
			}
		}
	}
}
