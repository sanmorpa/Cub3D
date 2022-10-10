SRCS	=	main.c exits.c ./parser/filler.c ./parser/parser.c \
			./parser/parse_info.c ./parser/parse_fc.c outils.c \
			./parser/parse_map.c ./mlx_items/images.c ./minimap/window.c ./movement.c \
			./raycaster/raycaster.c ./mlx_items/colors.c

NAME	=	cub3D

DIRLIBFT =  ./libft/libft.a

DIRGNL		= ./gnl/get_next_line.a

MAKELIBFT = cd ./libft/ && ${MAKE}

MAKEGNL = cd ./gnl/ && ${MAKE}

OBJS	=	${SRCS:.c=.o}

CFLAGS	=	-Wall -Wextra -Werror -I /usr/local/include #-g3 -fsanitize=address

MINILIBX = -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

CC		=	gcc

RM		=	rm -f

all:		${NAME}

${NAME}:	${OBJS}
			${MAKELIBFT}
			${MAKEGNL}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${MINILIBX} ${DIRLIBFT} ${DIRGNL}

clean:
			${RM} ${OBJS}
			${MAKELIBFT} clean
			${MAKEGNL} clean

fclean:		clean
			${RM} ${NAME}
			${MAKELIBFT} fclean
			${MAKEGNL} fclean

re:			fclean ${NAME}
			${MAKELIBFT} re
			${MAKEGNL} re

.PHONY:		all clean fclean re
