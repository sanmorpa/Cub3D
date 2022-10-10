/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:20:29 by samoreno          #+#    #+#             */
/*   Updated: 2022/10/10 13:23:37 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

unsigned long	rgb_to_hex(int r, int g, int b)
{
	unsigned long	hex;

	hex = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (hex);
}

void	my_mlx_pixel_put(t_image *img, int x, int y, uint32_t color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < img->width && y < img->height)
	{
		dst = img->mem_adress + (y * img->size_line + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

uint32_t	my_mlx_pixel_get(t_image *img, int x, int y)
{
	unsigned int	dst;
	uint32_t		color;

	if (x >= 0 && y >= 0 && x <= img->width && y < img->height)
	{
		dst = *(unsigned int *)(img->mem_adress
				+ (y * img->size_line + x * (img->bpp / 8)));
		color = rgba_to_hex((dst >> 16) & 0xFF,
				(dst >> 8) & 0xFF, (dst) & 0xFF, (dst >> 24) & 0xFF);
		return (color);
	}
	return (0x00);
}
