/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:14:29 by frocha            #+#    #+#             */
/*   Updated: 2024/11/26 12:14:30 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void free_split_arrays(char **filename_extension)
{
    int i;

    i = 0;
    while(filename_extension[i])
    {
        free(filename_extension[i]);
        i++;
    }
    free(filename_extension);
}

void free_matrix(int **matrix_numbers, int length) {
    for (int i = 0; i < length; i++) {
        free(matrix_numbers[i]);
    }
    free(matrix_numbers);
}
