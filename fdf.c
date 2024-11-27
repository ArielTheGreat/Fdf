/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:48:03 by frocha            #+#    #+#             */
/*   Updated: 2024/11/26 11:48:04 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int main(int argc, char **argv)
{
    int fd;
    t_matrix_info *matrix;
    int **matrix_numbers;
    char *line;
    int i;

    matrix_numbers = NULL;
    matrix = malloc(sizeof(t_matrix_info));
    if (argc > 2 || check_file_extension(argv[1]) == 0)
        return (0);

    fd = open(argv[1], O_RDONLY);
    allocate_memory_and_set_memory(&matrix, &matrix_numbers, fd);
    close(fd);
    fd = open(argv[1], O_RDONLY);

    i = 0;
    while(i < matrix->length + 1)
    {
        line = get_next_line(fd);
        printf("%s\n",line);
        i++;
    }

    close(fd);
    //free matrix numbers int and poinetrs
    return (0);
}
