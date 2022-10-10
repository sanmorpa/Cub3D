SRCS	=	get_next_line_utils.c get_next_line.c

NAME	=	get_next_line.a

OBJS	=	${SRCS:.c=.o}

CFLAGS	=	-Wall -Wextra -Werror

CC		=	gcc

RM		=	rm -f

all:		${NAME}

${NAME}:	${OBJS}
			ar rcs ${NAME} ${OBJS}

clean:
			${RM} ${OBJS} ${B_OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean ${NAME}

.PHONY:		all clean fclean re