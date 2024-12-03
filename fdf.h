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
# include <math.h>
# include <stdio.h>
# include "MLX42/include/MLX42/MLX42.h"

# define WIDTH				1920
# define HEIGHT				1080
# define DEFAULT_COLOR		16777215 //white

typedef struct map_node
{
    int x_axis;
    int y_axis;
    int z_axis;
    int color;
}   t_map_node;

typedef struct s_fdf
{
	mlx_t		*mlx;
    mlx_image_t	*canvas;
	int		shift_x;
	int		shift_y;
    int    zoom;
    int     width;
    int     length;
    t_map_node  **map_node;
}				t_fdf;

void	hook(void *param);
void	key_hook(void *param);
void    mouse_hook(double xdelta, double ydelta, void *param);
int     check_file_extension(char *filename);
void    free_split_arrays(char **filename_extension);
void    allocate_memory(t_fdf *fdf_info);
t_fdf    *allocate_memory_and_set_memory(char* filename);
void    set_width_matrix(t_fdf *matrix,  char* filename);
void    set_length_matrix(t_fdf *matrix, char* filename);
void draw_matrix(t_fdf *fdf_info);
// void    free_matrix(int **matrix_numbers, int length);

#endif