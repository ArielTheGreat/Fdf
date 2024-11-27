/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:48:24 by frocha            #+#    #+#             */
/*   Updated: 2024/11/26 11:48:26 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct m_info
{
    int width;
    int length;
}   t_matrix_info;

int     check_file_extension(char *filename);
void    free_split_arrays(char **filename_extension);
void    allocate_memory(int width, int length, int ***matrix_numbers);
void    allocate_memory_and_set_memory(t_matrix_info **matrix, int ***matrix_numbers, int fd);
void    set_width_matrix(t_matrix_info **matrix, int fd);
void    set_length_matrix(t_matrix_info **matrix, int fd);
void    free_matrix(int **matrix_numbers, int length);

#endif