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

char	*get_color_hex(char *color)
{
	char	*str;
	int		x;
	int		i;

	if (color == NULL)
		return (ft_strdup("ffffff"));
	str = malloc(sizeof(char) * 7);
	if (!str)
	{
		perror("Memory allocation error for color hex");
		return (NULL);
	}
	x = 2;
	i = 0;
	while (color[x] != '\0' && i < 6)
	{
		str[i] = color[x];
		i++;
		x++;
	}
	str[i] = '\0';
	return (str);
}

void	process_color_split(char **color_split, t_map_node *matrix_row, int i)
{
	matrix_row[i].z_axis = ft_atoi(color_split[0]);
	matrix_row[i].color = get_color_hex(color_split[1]);
	if (!matrix_row[i].color)
		perror("Error allocating memory for color");
	free_split_arrays(color_split);
}

void	process_words(char **words, t_map_node *matrix_row)
{
	char	**color_split;
	int		i;

	i = 0;
	while (words[i])
	{
		color_split = ft_split(words[i], ',');
		if (!color_split)
		{
			perror("Error splitting color");
			break ;
		}
		process_color_split(color_split, matrix_row, i);
		if (!matrix_row[i].color)
			break ;
		i++;
	}
}

void	set_numbers(char *str, t_map_node *matrix_row)
{
	char	**words;

	words = ft_split(str, ' ');
	if (!words)
	{
		perror("Error splitting line");
		return ;
	}
	process_words(words, matrix_row);
	free_split_arrays(words);
}

void	process_file(const char *filename, t_fdf *fdf_info)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return ;
	}
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		set_numbers(line, fdf_info->map_node[i]);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
}
