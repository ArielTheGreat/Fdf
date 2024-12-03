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

void set_length_matrix(t_fdf *matrix, char* filename)
{
    int i;
    int fd;

    fd = open(filename, O_RDONLY);
    i = 0;
    while(get_next_line(fd))
        i++;
    (matrix)->length = i;
    close(fd);
}

void    set_width_matrix(t_fdf *matrix, char *filename)
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
    (matrix)->width = i;
    free_split_arrays(words);
    close(fd);
}

void allocate_memory(t_fdf *fdf_info)
{
    int i;

    i = 0;
    fdf_info->map_node = malloc(sizeof(t_map_node *) * fdf_info->length);
    while(i < fdf_info->length)
    {
        fdf_info->map_node[i] = malloc(sizeof(t_map_node) * fdf_info->width);
        i++;
    }
}

t_fdf    *allocate_memory_and_set_memory(char* filename)
{
    static t_fdf fdf_info;

    set_width_matrix(&fdf_info, filename);
    set_length_matrix(&fdf_info, filename);
    if (fdf_info.width > 0 && fdf_info.length > 0)
        allocate_memory(&fdf_info);
    return (&fdf_info);
}
