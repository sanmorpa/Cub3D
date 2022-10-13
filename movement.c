/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:16:27 by josuna-t          #+#    #+#             */
/*   Updated: 2022/10/13 11:36:57 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	checkcolisions(t_content *ptrs)
{
	double	x;
	double	y;

	modf((double)ptrs->player.ncordx, &x);
	modf((double)ptrs->player.ncordy, &y);
	if (ptrs->map.map[(int)y][(int)x] != '1')
	{
		ptrs->map.map[(int)y][(int)x] = 'N';
		return (0);
	}
	return (1);
}

static void	turn_player(t_content *info, double rotspeed)
{
	double	olddirx;
	double	oldplanex;

	olddirx = info->player.dirx;
	oldplanex = info->player.planex;
	info->player.dirx = info->player.dirx * cos(rotspeed)
		- info->player.diry * sin(rotspeed);
	info->player.diry = olddirx * sin(rotspeed) + info->player.diry
		* cos(rotspeed);
	info->player.planex = info->player.planex * cos(rotspeed)
		- info->player.planey * sin(rotspeed);
	info->player.planey = oldplanex * sin(rotspeed) + info->player.planey
		* cos(rotspeed);
}

int	movecharacter(void *ptr)
{
	t_content	*ptrs;

	ptrs = ptr;
	ptrs->player.ncordx = ptrs->player.x;
	ptrs->player.ncordy = ptrs->player.y;
	if (ptrs->player.keypressed == RIGHT)
	{
		ptrs->player.ncordx -= ptrs->player.diry * 0.1;
		ptrs->player.ncordy += ptrs->player.dirx * 0.1;
	}
	if (ptrs->player.keypressed == LEFT)
	{
		ptrs->player.ncordx += ptrs->player.diry * 0.1;
		ptrs->player.ncordy -= ptrs->player.dirx * 0.1;
	}
	if (ptrs->player.keypressed == UP)
	{
		ptrs->player.ncordx += ptrs->player.dirx * 0.1;
		ptrs->player.ncordy += ptrs->player.diry * 0.1;
	}
	if (ptrs->player.keypressed == DOWN)
	{
		ptrs->player.ncordx -= ptrs->player.dirx * 0.1;
		ptrs->player.ncordy -= ptrs->player.diry * 0.1;
	}
	if (ptrs->player.rotpressed == L_TURN)
		turn_player(ptrs, 6.2);
	if (ptrs->player.rotpressed == R_TURN)
		turn_player(ptrs, -6.2);
	if (checkcolisions(ptrs) == 0)
	{
		ptrs->player.x = ptrs->player.ncordx;
		ptrs->player.y = ptrs->player.ncordy;
	}
	raycaster(*ptrs, -1);
	print_minimap(*ptrs);
	ptr = ptrs;
	usleep(10000);
	return (0);
}

int	movemouse(int x, int y, void *ptr)
{
	t_content	*ptrs;

	ptrs = ptr;
	(void)y;
	if (x > 0)
		ptrs->player.rotpressed = R_TURN;
	if (x < 0)
		ptrs->player.rotpressed = L_TURN;
	return (0);
}

int	keypress(int keycode, void *ptr)
{
	t_content	*ptrs;

	ptrs = ptr;
	if (keycode == ESC)
		ft_exit(ptrs, 0, 0, "Cerrado manualmente por el jugador\n");
	if (keycode == R_TURN || keycode == L_TURN)
		ptrs->player.rotpressed = keycode;
	if ((keycode == RIGHT || keycode == LEFT)
		|| keycode == UP || keycode == DOWN)
		ptrs->player.keypressed = keycode;
	ptr = ptrs;
	return (0);
}

int	keyrelease(int keycode, void *ptr)
{
	t_content	*ptrs;

	ptrs = ptr;
	if (ptrs->player.keypressed == keycode)
		ptrs->player.keypressed = -1;
	if (ptrs->player.rotpressed == keycode)
		ptrs->player.rotpressed = -1;
	ptr = ptrs;
	return (0);
}
