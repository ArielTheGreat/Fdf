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

void set_numbers(char *str, int *matrix_row)
{
    char **words;
    int i;

    words = ft_split(str,' ');
    if (!words) {
        perror("Error splitting line");
        return;
    }
    i = 0;
    while(words[i])
    {
        matrix_row[i] = ft_atoi(words[i]);
        i++;
    }
    free_split_arrays(words);
}

void process_file(const char *filename, int ***matrix_numbers) {
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
        set_numbers(line, (*matrix_numbers)[i]);
        free(line);
        i++;
    }

    close(fd);
}

void print_matrix(int **matrix_numbers, t_matrix_info *matrix) {
    for (int i = 0; i < matrix->length + 1; i++) {
        for (int j = 0; j < matrix->width; j++) {
            printf("%d ", matrix_numbers[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char **argv)
{
    int fd;
    t_matrix_info *matrix;
    int **matrix_numbers;

    matrix_numbers = NULL;
    matrix = malloc(sizeof(t_matrix_info));
    if (argc > 2 || check_file_extension(argv[1]) == 0)
        return (0);

    fd = open(argv[1], O_RDONLY);
    allocate_memory_and_set_memory(&matrix, &matrix_numbers, fd);
    close(fd);
    process_file(argv[1], &matrix_numbers);
    print_matrix(matrix_numbers, matrix);
    free_matrix(matrix_numbers, matrix->length + 1);
    free(matrix);
    return (0);
}
