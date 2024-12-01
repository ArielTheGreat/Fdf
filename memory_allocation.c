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

void set_length_matrix(t_matrix_info **matrix, char* filename)
{
    int i;
    int fd;

    fd = open(filename, O_RDONLY);
    i = 0;
    while(get_next_line(fd))
        i++;
    (*matrix)->length = i;
    close(fd);
}

void    set_width_matrix(t_matrix_info **matrix, char *filename)
{
    char *first_line;
    char **words;
    int i;
    int fd;

    i = 0;
    fd = open(filename, O_RDONLY);
    first_line = get_next_line(fd);
    words = ft_split(first_line, ' ');
    while(words[i])
        i++;
    (*matrix)->width = i;
    free_split_arrays(words);
    close(fd);
}

void allocate_memory(int width, int length, t_map_node ***array_struct_map)
{
    int i;

    i = 0;
    *array_struct_map = malloc(sizeof(t_map_node *) * length);
    while(i < length)
    {
        (*array_struct_map)[i] = malloc(sizeof(t_map_node) * width);
        i++;
    }
}

void    allocate_memory_and_set_memory(t_matrix_info **matrix, t_map_node ***array_struct_map, char* filename)
{
    set_width_matrix(matrix, filename);
    set_length_matrix(matrix, filename);
    if ((*matrix)->width > 0 && (*matrix)->length > 0)
        allocate_memory((*matrix)->width, (*matrix)->length, array_struct_map);
}
