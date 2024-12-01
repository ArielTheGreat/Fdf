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
# include "MLX42/include/MLX42/MLX42.h"

# define WIDTH				1920
# define HEIGHT				1080

typedef struct s_fdf
{
	mlx_t		*mlx;
    mlx_image_t	*canvas;
}				t_fdf;

typedef struct m_info
{
    int width;
    int length;
}   t_matrix_info;

typedef struct map_node
{
    int x_axis;
    int y_axis;
    int z_axis;
    int color;
}   t_map_node;

int     check_file_extension(char *filename);
void    free_split_arrays(char **filename_extension);
void    allocate_memory(int width, int length, t_map_node ***array_struct_map);
void    allocate_memory_and_set_memory(t_matrix_info **matrix, t_map_node ***array_struct_map, char* filename);
void    set_width_matrix(t_matrix_info **matrix,  char* filename);
void    set_length_matrix(t_matrix_info **matrix, char* filename);
void    free_matrix(int **matrix_numbers, int length);

#endif