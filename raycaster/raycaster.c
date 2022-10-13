/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:25:25 by samoreno          #+#    #+#             */
/*   Updated: 2022/10/13 15:31:42 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	aux_fill(t_ray *ray, t_content info)
{
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (info.player.x - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->mapx + 1.0 - info.player.x) * ray->deltadistx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (info.player.y - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->mapy + 1.0 - info.player.y) * ray->deltadisty;
	}
}

static t_ray	fill_raycaster(t_content info, int x)
{
	t_ray	ray;

	ray.camerax = 2 * x / (double)W - 1;
	ray.raydirx = info.player.dirx + info.player.planex * ray.camerax;
	ray.raydiry = info.player.diry + info.player.planey * ray.camerax;
	ray.mapx = (int)info.player.x;
	ray.mapy = (int)info.player.y;
	if (ray.raydirx == 0)
		ray.deltadistx = 1e30;
	else
		ray.deltadistx = fabs(1 / ray.raydirx);
	if (ray.raydiry == 0)
		ray.deltadisty = 1e30;
	else
		ray.deltadisty = fabs(1 / ray.raydiry);
	ray.hit = 0;
	aux_fill(&ray, info);
	return (ray);
}

static t_image	choose_image(t_ray *ray, t_content info)
{
	if (ray->side == 0 && ray->raydirx < 0)
		return (info.images.no);
	else if (ray->side == 0 && ray->raydirx > 0)
		return (info.images.so);
	else if (ray->side == 1 && ray->raydiry < 0)
		return (info.images.we);
	return (info.images.ea);
}

void	cast_texture(t_content info, t_ray *ray, int x, t_image *to_print)
{
	t_image		img;
	int			y;
	uint32_t	color;
	int			pitch;

	pitch = 100;
	y = -1;
	img = choose_image(ray, info);
	ray->texx = (int)(ray->wallx * (double)(img.width));
	if ((ray->side == 0 && ray->raydirx > 0) || (ray->side == 1 && ray->raydiry < 0))
		ray->texx = img.width - ray->texx - 1;
	ray->step = 1.0 * img.height / ray->lineheight;
	ray->texpos = (ray->drawstart - pitch - H / 2 + ray->lineheight / 2) * ray->step;
	while (++y <= ray->drawstart)
		my_mlx_pixel_put(to_print, x, y, info.images.c);
	while (y <= ray->drawend)
	{
		ray->texy = (int)ray->texpos;
		ray->texpos += ray->step;
		color = my_mlx_pixel_get(&img, ray->texx, ray->texy);
		my_mlx_pixel_put(to_print, x, y++, color);
	}
	while (y < H)
		my_mlx_pixel_put(to_print, x, y++, info.images.f);
}

static void	draw_ray(t_content info, t_ray *ray, int x, t_image *to_print)
{
	int	pitch;

	pitch = 100;
	if (ray->side == 0)
	{
		ray->prepwalldist = ray->sidedistx - ray->deltadistx;
		ray->wallx = info.player.y + ray->prepwalldist + ray->raydiry;
	}
	else
	{
		ray->prepwalldist = ray->sidedisty - ray->deltadisty;
		ray->wallx = info.player.x + ray->prepwalldist + ray->raydirx;
	}
	ray->wallx -= floor(ray->wallx);
	ray->lineheight = (int)(H / ray->prepwalldist);
	ray->drawstart = -ray->lineheight / 2 + H / 2 + pitch;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = ray->lineheight / 2 + H / 2 + pitch;
	if (ray->drawend >= H)
		ray->drawend = H - 1;
	cast_texture(info, ray, x, to_print);
}

void	raycaster(t_content info, int start)
{
	t_ray	ray;
	t_image	to_print;

	to_print.ptr = mlx_new_image(info.mlx_ptr, W, H);
	to_print.height = H;
	to_print.width = W;
	to_print.mem_adress = mlx_get_data_addr(to_print.ptr, &to_print.bpp, &to_print.size_line, &to_print.endian);
	while (++start < W)
	{
		ray = fill_raycaster(info, start);
		while (ray.hit == 0)
		{
			if (ray.sidedistx < ray.sidedisty)
			{
				ray.sidedistx += ray.deltadistx;
				ray.mapx += ray.stepx;
				ray.side = 0;
			}
			else
			{
				ray.sidedisty += ray.deltadisty;
				ray.mapy += ray.stepy;
				ray.side = 1;
			}
			if (info.map.map[ray.mapy][ray.mapx] == '1')
				ray.hit = 1;
		}
		draw_ray(info, &ray, start, &to_print);
	}
	mlx_put_image_to_window(info.mlx_ptr, info.win_ptr, to_print.ptr, 0, 0);
	mlx_destroy_image(info.mlx_ptr, to_print.ptr);
}
