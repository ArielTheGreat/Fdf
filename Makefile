# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/26 12:28:00 by frocha            #+#    #+#              #
#    Updated: 2024/11/26 12:28:01 by frocha           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = fdf.c check_file_extension.c free_functions.c memory_allocation.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c hooks.c

OBJS = ${SRCS:.c=.o}
INCLUDE		=	-I.

NAME = fdf

MLX42/build/libmlx42.a:
	cd MLX42 && cmake -B build && make -C build -j4

$(NAME): ${OBJS} MLX42/build/libmlx42.a
	@make all -C ./libft
	${CC} ${CFLAGS}  $^ ${INCLUDE} -Llibft -lft -LMLX42/build -lmlx42 -lglfw -lm -o ${NAME}

all: $(NAME)

clean:
	@make clean -C ./libft
	@rm -f ${OBJS}

fclean: clean
	@make fclean -C ./libft
	@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
