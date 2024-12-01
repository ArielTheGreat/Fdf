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

int convert_hex_to_int(char *color_element)
{
    int size_str;
    char *hex_str;
    int i;
    int j;

    size_str = ft_strlen(color_element);
    hex_str = malloc(sizeof(char) * (size_str - 1));
    i = 0;
    j = 2;
    while(i <= size_str - 2)
    {
        hex_str[i] = color_element[j];
        i++;
        j++;
    }
    // printf("%s\n", hex_str);
    free(hex_str);
    return (size_str);
}

int get_color_int(char *color_element)
{
    int i;

    i = 0;
    if (color_element && ft_strlen(color_element) > 2)
    {
        return (convert_hex_to_int(color_element));
    }
    return (DEFAULT_COLOR);
}

void set_numbers(char *str, t_map_node *matrix_row, int row)
{
    char **words;
    int i;
    char **color_split;

    words = ft_split(str,' ');
    if (!words) {
        perror("Error splitting line");
        return;
    }
    i = 0;
    while(words[i])
    {
        color_split = ft_split(words[i], ',');
        (matrix_row+i)->x_axis = i;
        (matrix_row+i)->y_axis = row;
        (matrix_row+i)->z_axis = ft_atoi(color_split[0]);
        (matrix_row+i)->color = get_color_int(color_split[1]);
        i++;
        free(color_split);
    }
    free_split_arrays(words);
}

void process_file(const char *filename, t_map_node ***matrix_numbers) 
{
    int fd;
    char *line;
    int i = 0;

    line = NULL;
    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }

    while ((line = get_next_line(fd))) {
        set_numbers(line, (*matrix_numbers)[i], i);
        free(line);
        i++;
    }

    close(fd);
}

// t_fdf  *start_fdf()
// {
//     static t_fdf	fdf;

//     fdf.mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
//     fdf.canvas = mlx_new_image(fdf.mlx, WIDTH, HEIGHT);
//     return (&fdf);
// }

void print_matrix(t_map_node **matrix_numbers, t_matrix_info *matrix) {
    for (int i = 0; i < matrix->length; i++) {
        for (int j = 0; j < matrix->width; j++) {
            printf("%d,%d,%d,%d ", (&matrix_numbers[i][j])->x_axis, (&matrix_numbers[i][j])->y_axis, (&matrix_numbers[i][j])->z_axis, (&matrix_numbers[i][j])->color);
        }
        printf("\n");
    }
}

int main(int argc, char **argv)
{
    // t_fdf		*fdf;
    t_matrix_info *matrix;
    t_map_node **array_struct_map;

    array_struct_map = NULL;
    matrix = malloc(sizeof(t_matrix_info));
    if (argc > 2 || check_file_extension(argv[1]) == 0)
        return (0);
    // fdf = start_fdf();
    allocate_memory_and_set_memory(&matrix,  &array_struct_map, argv[1]);
    process_file(argv[1], &array_struct_map);
    print_matrix(array_struct_map, matrix);
    // mlx_terminate(fdf->mlx);
    //free_matrix(array_struct_map, matrix->length + 1);
    free(matrix);
    return (0);
}
