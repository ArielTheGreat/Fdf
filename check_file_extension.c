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
	char	*filename_extension;

	if (!filename)
		return (0);
	filename_extension = ft_strchr(filename, '.');
	while (filename != NULL)
	{
		filename_extension = filename;
		filename++;
	}
	if (!filename_extension
		|| ft_strncmp(filename_extension + 1, "fdf", 3) != 0
		|| filename_extension[4] != '\0')
		return (0);
	return (1);
}
