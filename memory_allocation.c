/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_allocation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 21:43:49 by frocha            #+#    #+#             */
/*   Updated: 2024/11/26 21:43:50 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void set_length_matrix(t_matrix_info **matrix, int fd)
{
    int i;

    i = 0;
    while(get_next_line(fd))
        i++;
    (*matrix)->length = i;
}

void    set_width_matrix(t_matrix_info **matrix, int fd)
{
    char *first_line;
    char **words;
    int i;

    i = 0;
    first_line = get_next_line(fd);
    words = ft_split(first_line, ' ');
    while(words[i])
        i++;
    (*matrix)->width = i;
    free_split_arrays(words);
}

void allocate_memory(t_matrix_info **matrix, int **matrix_numbers)
{
    int i;

    i = 0;
    matrix_numbers = malloc(sizeof(int *) * (*matrix)->length);
    while(i > (*matrix)->length)
    {
        matrix_numbers[i] = malloc(sizeof(int) * (*matrix)->width);
        i++;
    }
}

void set_numbers_for_matrix(t_matrix_info **matrix, int **matrix_numbers, int fd)
{
    int i;
    int j;
    char *line;
    char **words;

    i = 0;
    while(i < (*matrix)->length)
    {
        j = 0;
        line = get_next_line(fd);
        words = ft_split(line, ' ');
        while(words[j])
        {
            matrix_numbers[i][j] = ft_atoi(words[j]);
            j++;
        }
        free_split_arrays(words);
        i++;
    }
}

void    allocate_memory_and_set_memory(t_matrix_info **matrix, int **matrix_numbers, int fd)
{
    set_width_matrix(matrix, fd);
    set_length_matrix(matrix, fd);
    allocate_memory(matrix, matrix_numbers);
    set_numbers_for_matrix(matrix, matrix_numbers, fd);
}
