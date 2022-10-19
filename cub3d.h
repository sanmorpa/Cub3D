/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 10:13:55 by samoreno          #+#    #+#             */
/*   Updated: 2022/10/13 11:37:51 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"

# define ESC		53
# define UP			13
# define LEFT		0
# define DOWN		1
# define RIGHT		2
# define L_TURN		123
# define R_TURN		124
# define MINI_TILE	20
# define IMG_SIZE	1080
# define ANGLE		90
# define W			1024
# define H			600
# define TRANS		0xFF000000
# define GREEN		0x00006400
# define GREY		0x20D3D3D3
# define ORANGE		0x0000008B
# define RED		0x206D2F2E
# define BLUE		0x001167B1
# define L_ORANGE	0x00EE9F27
# define D_ORANGE	0x00D24E01
# define L_PINK		0x00FE7F9C
# define D_PINK		0x009E4244

typedef struct s_ptr
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_ptr;

typedef struct s_map
{
	int		x;
	int		y;
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
}	t_map;

typedef struct s_image
{
	int		height;
	int		width;
	void	*ptr;
	char	*mem_adress;
	int		bpp;
	int		size_line;
	int		endian;
}	t_image;

typedef struct s_images
{
	t_image			no;
	t_image			so;
	t_image			we;
	t_image			ea;
	unsigned long	f;
	unsigned long	c;
}	t_images;

typedef struct s_player
{
	double	x;
	double	y;
	float	ncordx;
	float	ncordy;
	float	xcoord;
	float	ycoord;
	double	planex;
	double	planey;
	double	dirx;
	double	diry;
	int		keypressed;
	int		rotpressed;
}	t_player;

typedef struct s_content
{
	t_map		map;
	t_images	images;
	void		*mlx_ptr;
	void		*win_ptr;
	t_player	player;
}	t_content;

typedef struct s_ray
{
	double	camerax;
	double	raydirx;
	double	raydiry;
	int		mapx;
	int		mapy;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	prepwalldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		drawstart;
	int		drawend;
	int		lineheight;
	double	wallx;
	double	wally;
	int		texx;
	int		texy;
	double	step;
	double	texpos;
}	t_ray;

int				error_msg(char *msg);
t_map			parse_map(char *map);
void			ft_exit(t_content *info, int code, int error, char *msg);
int				ft_free(char **array, int words);
t_map			count_lines(char *file);
char			**fill_map(int fd, t_map *info);
int				parse_info(t_map *map);
int				free_infos(t_map *map);
int				input_errors(int argc, char**argv);
int				count_split(char **split);
int				parse_fc(char *c, char *f);
int				check_map(t_map *map);
void			initial_coordinates(int *coord, char **map);
void			init_null(t_map *map);
t_images		fill_images(t_content *info);
void			destroy_images(t_content *info, t_images *images);
t_images		fill_minimap(t_content *info);
void			print_minimap(t_content info);
t_images		initialize_images(void);
int				ft_red_cross(t_content *info);
t_player		position_player(char **map);
int				keypress(int keycode, void *ptr);
int				keyrelease(int keycode, void *ptr);
int				movemouse(int x, int y, void *ptr);
int				movecharacter(void *ptr);
void			raycaster(t_content info, int start);
unsigned long	rgba_to_hex(int r, int g, int b, int a);
unsigned long	rgb_to_hex(int r, int g, int b);
void			my_mlx_pixel_put(t_image *img, int x, int y, uint32_t color);
uint32_t		my_mlx_pixel_get(t_image *img, int x, int y);
#endif
