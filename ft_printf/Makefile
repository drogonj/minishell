SRCS		=	ft_printf.c \
				ft_output.c \
				ft_putstr.c \
				ft_putnbr.c \
				ft_puthex.c \
				ft_putpointer.c \
				ft_isformat.c \
				ft_argcount.c 

NAME		=	libftprintf.a

OBJS		=	${SRCS:.c=.o}

FLAGS		=	-Wall -Wextra -Werror

GCC			=	gcc

RM			=	rm -f

all:		${NAME}

.c.o:
			${GCC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			ar rc ${NAME} ${OBJS}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
