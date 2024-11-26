/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_extension.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:47:48 by frocha            #+#    #+#             */
/*   Updated: 2024/11/26 11:47:53 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int check_file_extension(char *filename)
{
    char **filename_extension;

    filename_extension = ft_split(filename,'.');

    if (ft_strncmp(filename_extension[1], "fdf", 4) != 0)
    {
        free_split_arrays(filename_extension);
        return (0);
    }

    free_split_arrays(filename_extension);
    return (1);
}
