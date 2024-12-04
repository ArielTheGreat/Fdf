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
# define FDF_H

# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "MLX42/include/MLX42/MLX42.h"

# define WIDTH				1920
# define HEIGHT				1080
# define DEFAULT_COLOR		16777215 // White

typedef struct map_node
{
	int		z_axis;
	int		color;
}	t_map_node;

typedef struct s_fdf
{
	mlx_t		*mlx;
	mlx_image_t	*canvas;
	int			shift_x;
	int			shift_y;
	int			*sx;
	int			*sy;
	int			zoom;
	int			width;
	int			length;
	t_map_node	**map_node;
}	t_fdf;

/* Hooks */
void	hook(void *param);
void	key_hook(void *param);
void	mouse_hook(double xdelta, double ydelta, void *param);

/* Transformations */
void	isometric(int *x, int *y, int z);
void	zoom(t_fdf *point, int *begin, int *end);
void	shift(t_fdf *point, int *begin, int *end);

/* File Checking and Parsing */
int		check_file_extension(char *filename);
void	free_split_arrays(char **filename_extension);
void	set_width_matrix(t_fdf *matrix, char *filename);
void	set_length_matrix(t_fdf *matrix, char *filename);
void	process_file(const char *filename, t_fdf *fdf_info);

/* Memory Management */
void	allocate_memory(t_fdf *fdf_info);
t_fdf	*allocate_memory_and_set_memory(char *filename);
// void	free_matrix(int **matrix_numbers, int length);

/* Drawing */
void	draw_matrix(t_fdf *fdf_info);
void	wu_algo(t_fdf *fdf_info, int *begin, int *end);
void	draw_pix(t_fdf *point, int *begin, int *end);

/* Color Conversion */
int		get_color_int(char *color_element);
int		convert_hex_to_int(char *color_element);
int		get_index_hex(char character, int size_str);
int		get_base_multiplication(int size_str);

/* Line Parsing */
void	set_numbers(char *str, t_map_node *matrix_row);

/* Steep Calculation */
int		get_steep_sx(int *x, int *x1, t_fdf *point);
int		get_steep_sy(int *y, int *y1, t_fdf *point);

#endif
