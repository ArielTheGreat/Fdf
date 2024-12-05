/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_allocation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 21:43:49 by frocha            #+#    #+#             */
/*   Updated: 2024/11/26 21:43:50 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_length_matrix(t_fdf *matrix, char *filename)
{
	int		i;
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return ;
	}
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	matrix->length = i;
	close(fd);
}

static int	count_words_in_line(char *line)
{
	char	**words;
	int		count;

	words = ft_split(line, ' ');
	if (!words)
	{
		perror("Error splitting line");
		return (-1);
	}
	count = 0;
	while (words[count])
		count++;
	free_split_arrays(words);
	return (count);
}

void	set_width_matrix(t_fdf *matrix, char *filename)
{
	char	*first_line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return ;
	}
	first_line = get_next_line(fd);
	close(fd);
	if (!first_line)
	{
		perror("Error reading first line");
		matrix->width = 0;
		return;
	}
	matrix->width = count_words_in_line(first_line);
	free(first_line);
}

void	allocate_memory(t_fdf *fdf_info)
{
	int	i;

	i = 0;
	fdf_info->map_node = malloc(sizeof(t_map_node *) * fdf_info->length);
	if (!fdf_info->map_node)
	{
		perror("Memory allocation error");
		return ;
	}
	while (i < fdf_info->length)
	{
		fdf_info->map_node[i] = malloc(sizeof(t_map_node) * fdf_info->width);
		if (!fdf_info->map_node[i])
		{
			perror("Memory allocation error");
			while (--i >= 0)
				free(fdf_info->map_node[i]);
			free(fdf_info->map_node);
			fdf_info->map_node = NULL;
			return ;
		}
		i++;
	}
}

t_fdf	*allocate_memory_and_set_memory(char *filename)
{
	static t_fdf	fdf_info;

	fdf_info.width = 0;
	fdf_info.length = 0;
	fdf_info.map_node = NULL;
	set_width_matrix(&fdf_info, filename);
	set_length_matrix(&fdf_info, filename);
	if (fdf_info.width > 0 && fdf_info.length > 0)
		allocate_memory(&fdf_info);
	return (&fdf_info);
}
