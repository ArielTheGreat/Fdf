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

int	check_file_extension(char *filename)
{
	if (!filename)
		return (0);
	filename = ft_strchr(filename, '.');
	if (!filename
		|| ft_strncmp(filename + 1, "fdf", 3) != 0
		|| filename[4] != '\0')
		return (0);
	return (1);
}
