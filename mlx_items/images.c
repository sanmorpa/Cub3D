/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:45:00 by samoreno          #+#    #+#             */
/*   Updated: 2022/10/10 13:20:49 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	fill_colors(t_content *info, t_images *images)
{
	int	i;
	int	rgb[3];

	i = 1;
	rgb[0] = ft_atoi(info->map.c);
	while (info->map.c[i] && info->map.c[i - 1] != ',')
		i++;
	rgb[1] = ft_atoi(&info->map.c[i]);
	i++;
	while (info->map.c[i] && info->map.c[i - 1] != ',')
		i++;
	rgb[2] = ft_atoi(&info->map.c[i]);
	images->c = rgb_to_hex(rgb[0], rgb[1], rgb[2]);
	i = 1;
	rgb[0] = ft_atoi(info->map.f);
	while (info->map.f[i] && info->map.f[i - 1] != ',')
		i++;
	rgb[1] = ft_atoi(&info->map.f[i]);
	i++;
	while (info->map.f[i] && info->map.f[i - 1] != ',')
		i++;
	rgb[2] = ft_atoi(&info->map.f[i]);
	images->f = rgb_to_hex(rgb[0], rgb[1], rgb[2]);
}

void	destroy_images(t_content *info, t_images *images)
{
	if (!images->no.ptr || !images->so.ptr || !images->we.ptr
		|| !images->ea.ptr)
		error_msg(NULL);
	if (images->no.ptr)
		mlx_destroy_image(info->mlx_ptr, images->no.ptr);
	if (images->so.ptr)
		mlx_destroy_image(info->mlx_ptr, images->so.ptr);
	if (images->we.ptr)
		mlx_destroy_image(info->mlx_ptr, images->we.ptr);
	if (images->ea.ptr)
		mlx_destroy_image(info->mlx_ptr, images->ea.ptr);
	if (info->win_ptr)
		mlx_destroy_window(info->mlx_ptr, info->win_ptr);
	info->mlx_ptr = NULL;
}

t_image	fill_per_image(t_content *info, char *dir)
{
	t_image	img;

	img.ptr = mlx_xpm_file_to_image(info->mlx_ptr, dir,
			&img.width, &img.height);
	if (!img.ptr)
		return (img);
	img.mem_adress = mlx_get_data_addr(img.ptr, &img.bpp, &img.size_line,
			&img.endian);
	return (img);
}

t_images	fill_images(t_content *info)
{
	t_images	images;

	images.ea.ptr = NULL;
	images.no.ptr = NULL;
	images.so.ptr = NULL;
	images.we.ptr = NULL;
	info->mlx_ptr = mlx_init();
	if (!info->mlx_ptr)
		return (images);
	info->win_ptr = mlx_new_window(info->mlx_ptr, W, H, "cub3D");
	if (!info->win_ptr)
	{
		destroy_images(info, &images);
		return (images);
	}
	images.no = fill_per_image(info, info->map.no);
	images.so = fill_per_image(info, info->map.so);
	images.ea = fill_per_image(info, info->map.ea);
	images.we = fill_per_image(info, info->map.we);
	if (!images.no.ptr || !images.so.ptr || !images.ea.ptr
		|| !images.we.ptr)
		destroy_images(info, &images);
	fill_colors(info, &images);
	return (images);
}
