/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_number_into_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:06:48 by frocha            #+#    #+#             */
/*   Updated: 2024/12/04 14:06:49 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_numbers(char *str, t_map_node *matrix_row)
{
	char	**words;
	char	**color_split;
	int		i;

	words = ft_split(str, ' ');
	if (!words)
	{
		perror("Error splitting line");
		return ;
	}
	i = 0;
	while (words[i])
	{
		color_split = ft_split(words[i], ',');
		if (!color_split)
		{
			perror("Error splitting color");
			break ;
		}
		matrix_row[i].z_axis = ft_atoi(color_split[0]);
		matrix_row[i].color = get_color_int(color_split[1]);
		free_split_arrays(color_split);
		i++;
	}
	free_split_arrays(words);
}

void	process_file(const char *filename, t_fdf *fdf_info)
{
	int		fd;
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return ;
	}
	line = get_next_line(fd);
	while (line)
	{
		set_numbers(line, fdf_info->map_node[i]);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
}