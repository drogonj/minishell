# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcherrie <fcherrie@student.42mulhouse.fr>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/20 13:05:32 by fcherrie          #+#    #+#              #
#    Updated: 2023/03/06 15:22:52 by ngalzand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=		minishell

SRC 		= 		main.c parsing.c splitline.c variable.c cat_variable.c init_cmd.c utils.c trans_quote.c redir_copy.c cut_cmd.c redir_exec.c\
					builtins/echo.c builtins/cd.c builtins/pwd.c builtins/export.c builtins/unset.c builtins/env.c builtins/exit.c \
					utils_2.c builtins/export_2.c builtins/export_3.c utils_3.c find_path_executables.c get_next_line/get_next_line.c \
					get_next_line/get_next_line_utils.c builtins/launch_executable.c handle_signals.c cat_pipe.c var_error.c builtins/shlvl.c pipe.c \
					utils_4.c

OBJS 		= 		${SRC:.c=.o}

LIBFT		=		libft/libft.a

FT_PRINTF	=		ft_printf/libftprintf.a

FLAGS 		= 		-Wall -Wextra -Werror #-g3 -fsanitize=address

.c.o:
					gcc ${FLAGS} -c $< -o ${<:.c=.o} -I /Users/$$USER/.brew/opt/readline/include/

all : 				${NAME}

${NAME}: 			${OBJS}
					${MAKE} -C libft

					${MAKE} -C ft_printf
					gcc ${FLAGS} -lreadline -L /Users/$$USER/.brew/opt/readline/lib/ ${OBJS} ${LIBFT} ${FT_PRINTF} -o ${NAME}

clean :
					${MAKE} -C libft clean
					${MAKE} -C ft_printf clean
					rm -f ${OBJS}

fclean: 			clean
					${MAKE} -C libft fclean
					${MAKE} -C ft_printf fclean
					rm -f ${NAME}

re : 				fclean all

.PHONY: 			all clean fclean re

