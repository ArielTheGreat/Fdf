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

int get_base_multiplication(int size_str)
{
    int result;
    int i;

    i = 0;
    result = 1;
    while(i < size_str)
    {
        result = result * 16;
        i++;
    }
    return (result);
}

int get_index_hex(char character, int size_str)
{
    char *hex_values;
    int i;

    hex_values = "0123456789ABCDEF";
    i = 0;
    while(hex_values[i] != character)
        i++;
    return (i * get_base_multiplication(size_str));
}

int convert_hex_to_int(char *color_element)
{
    int i;
    int result;
    int size_str;

    i = 2;
    result = 0;
    size_str = ft_strlen(color_element+i) - 1;
    while(color_element[i] != '\0')
    {
        result = result + get_index_hex(color_element[i], size_str);
        i++;
        size_str--;
    }
    return (result);
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
        free_split_arrays(color_split);
    }
    free_split_arrays(words);
}

void process_file(const char *filename, t_fdf *fdf_info) 
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
        set_numbers(line, fdf_info->map_node[i], i);
        free(line);
        i++;
    }

    close(fd);
}

void print_matrix(t_fdf *fdf_info) {
    for (int i = 0; i < fdf_info->length; i++) {
        for (int j = 0; j < fdf_info->width; j++) {
            printf("%d,%d ", (&fdf_info->map_node[i][j])->x_axis, (&fdf_info->map_node[i][j])->y_axis);
        }
        printf("\n");
    }
}

void iso_projection(int *x, int *y, int z)
{
    int prev_x = *x;
    int prev_y = *y;
    *x = (prev_x - prev_y) * cos(0.523599);
    *y = (prev_x + prev_y) * sin(0.523599) - z;
}

void draw_line(t_fdf *fdf, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        mlx_put_pixel(fdf->canvas, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = err * 2;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void apply_isometric_to_each_struct(t_fdf *fdf_info)
{
    for (int i = 0; i < fdf_info->length; i++)
    {
        for (int j = 0; j < fdf_info->width; j++)
        {
            int x = fdf_info->map_node[i][j].x_axis;
            int y = fdf_info->map_node[i][j].y_axis;
            int z = fdf_info->map_node[i][j].z_axis;

            iso_projection(&x, &y, z);

            fdf_info->map_node[i][j].x_axis = x;
            fdf_info->map_node[i][j].y_axis = y;
        }
    }
}

void draw_matrix(t_fdf *fdf_info)
{
    for (int i = 0; i < fdf_info->length; i++)
    {
        for (int j = 0; j < fdf_info->width; j++)
        {
            int x0 = fdf_info->map_node[i][j].x_axis;
            int y0 = fdf_info->map_node[i][j].y_axis;
            int x1, y1;

            x0 *= fdf_info->zoom;
            y0 *= fdf_info->zoom;

            x0 += fdf_info->shift_x;
            y0 += fdf_info->shift_y;

            if (j < fdf_info->width - 1)
            {
                x1 = fdf_info->map_node[i][j + 1].x_axis;
                y1 = fdf_info->map_node[i][j + 1].y_axis;
                x1 *= fdf_info->zoom;
                y1 *= fdf_info->zoom;
                x1 += fdf_info->shift_x;
                y1 += fdf_info->shift_y;
                draw_line(fdf_info, x0, y0, x1, y1, fdf_info->map_node[i][j].color);
            }

            if (i < fdf_info->length - 1)
            {
                x1 = fdf_info->map_node[i + 1][j].x_axis;
                y1 = fdf_info->map_node[i + 1][j].y_axis;
                x1 *= fdf_info->zoom;
                y1 *= fdf_info->zoom;
                x1 += fdf_info->shift_x;
                y1 += fdf_info->shift_y;
                draw_line(fdf_info, x0, y0, x1, y1, fdf_info->map_node[i][j].color);
            }
        }
    }
}

int main(int argc, char **argv)
{
    t_fdf		*fdf;

    if (argc > 2 || check_file_extension(argv[1]) == 0)
        return (0);
    fdf = allocate_memory_and_set_memory(argv[1]);
    process_file(argv[1],   fdf);
    print_matrix(fdf);
    fdf->mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
    fdf->canvas = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);

    apply_isometric_to_each_struct(fdf);
    printf("\n\n *********************************** \n");
    fdf->zoom = 5;
    fdf->shift_x = 300;
	fdf->shift_y = 300;
    print_matrix(fdf);
    draw_matrix(fdf);
    mlx_image_to_window(fdf->mlx, fdf->canvas, 0, 0);
    mlx_loop_hook(fdf->mlx, &hook, fdf);
    mlx_scroll_hook(fdf->mlx, &mouse_hook, fdf);
	mlx_loop_hook(fdf->mlx, &key_hook, fdf);
    mlx_loop(fdf->mlx);

    mlx_terminate(fdf->mlx);
    //free_matrix(array_struct_map, matrix->length + 1);
    // free(fdf);
    return (0);
}
