SRCS	=	main.c exits.c ./parser/filler.c ./parser/parser.c \
			./parser/parse_info.c ./parser/parse_fc.c outils.c \
			./parser/parse_map.c ./mlx_items/images.c ./minimap/window.c ./movement.c \
			./raycaster/raycaster.c ./mlx_items/colors.c

NAME = cub3D

CC = clang

CFLAGS = -Wall -Wextra -Werror -O2

INC = -I inc -I libft

LIBFT = ./libft/libft.a

GNL = ./gnl/get_next_line.a

ifeq ($(shell uname), Linux)
	INC += -I inc/linux -I mlx_linux
	MLX = ./mlx_linux/libmlx.a
	MLX_D = mlx_linux
	MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
else
	INC += -I inc/mac -I mlx_mac
	MLX = ./mlx_mac/libmlx.a
	MLX_D = mlx_mac
	MLX_FLAGS = -framework OpenGL -framework AppKit
endif

OBJS = $(SRCS:.c=.o)

MAKELIBFT = cd ./libft/ && ${MAKE}

MAKEGNL = cd ./gnl/ && ${MAKE}

MAKEMLX =  cd ./${MLX_D}/ && ${MAKE}

all:		${NAME}

${NAME}:	${OBJS}
			$(MAKELIBFT)
			$(MAKEGNL)
			$(MAKEMLX)
			$(CC) $(CFLAGS) $(INC) $(OBJS) $(LIBFT) $(GNL) $(MLX) $(MLX_FLAGS) -o $@

clean:
			rm -rf $(OBJS)
			$(MAKELIBFT) clean
			$(MAKEGNL) clean
			$(MAKEMLX) clean

fclean:		clean
			rm -rf $(NAME)
			$(MAKELIBFT) fclean
			$(MAKEGNL) fclean
			$(MAKEMLX) clean

re:			fclean all

.PHONY:		all clean fclean re bonus
