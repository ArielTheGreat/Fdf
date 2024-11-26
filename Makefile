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

SRC = check_file_extension.c fdf.c free_functions.c

OBJS = ${SRCS:.c=.o}
INCLUDE		=	-I.

NAME = fdf

$(NAME): ${OBJS}
	@make re -C ./libft
	${CC} ${CFLAGS}  $^ ${INCLUDE} -Llibft -lft -o ${NAME}

all: $(NAME)


.PHONY: all clean fclean