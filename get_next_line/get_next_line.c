/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:33:39 by frocha            #+#    #+#             */
/*   Updated: 2024/10/22 11:33:42 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*_set_line(char *line_buffer)
{
	int		counter;
	char	*str;

	if (!line_buffer)
		return (NULL);
	counter = 0;
	while (line_buffer[counter] != '\0' && line_buffer[counter] != '\n')
		counter++;
	if (line_buffer[counter] == '\n')
	{
		line_buffer[counter] = '\0';
		str = ft_strdup(line_buffer + counter + 1);
		if (str == NULL)
			return (NULL);
		line_buffer[counter] = '\n';
		line_buffer[counter + 1] = '\0';
	}
	else
		str = NULL;
	return (str);
}

char	*_join_and_process_buffer(char *str, char *buffer)
{
	char	*temp;
	char	*str1;

	if (!str)
	{
		str1 = ft_strdup(buffer);
		if (str1 == NULL)
		{
			return (NULL);
		}
		return (str1);
	}
	temp = ft_strjoin(str, buffer);
	if (temp == NULL)
	{
		free(str);
		return (NULL);
	}
	free(str);
	return (temp);
}

char	*_read_into_buffer(int fd, char *buffer, char *str)
{
	ssize_t	bytes_read;

	while (ft_strchr(str, '\n') == NULL)
	{
		bytes_read = read(fd, (void *)buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(str);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		str = _join_and_process_buffer(str, buffer);
		if (str == NULL)
			return (NULL);
	}
	return (str);
}

char	*_initialize_string(char **left_c)
{
	char	*str;

	if (*left_c != NULL)
	{
		str = ft_strdup(*left_c);
		if (str == NULL)
			return (NULL);
		free(*left_c);
		*left_c = NULL;
	}
	else
	{
		str = ft_strdup("");
		if (str == NULL)
			return (NULL);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	char			buffer[BUFFER_SIZE + 1];
	static char		*left_c;
	char			*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = _initialize_string(&left_c);
	if (str == NULL)
		return (NULL);
	str = _read_into_buffer(fd, buffer, str);
	if (str == NULL || str[0] == '\0')
	{
		free(str);
		return (NULL);
	}
	left_c = _set_line(str);
	return (str);
}
