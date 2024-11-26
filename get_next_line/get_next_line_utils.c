/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:33:57 by frocha            #+#    #+#             */
/*   Updated: 2024/10/22 11:34:00 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	int		counter;
	char	*str_dup;

	counter = 0;
	while (s1[counter] != '\0')
		counter++;
	counter++;
	str_dup = malloc(counter * sizeof(char));
	if (str_dup == NULL)
		return (NULL);
	counter = 0;
	while (s1[counter] != '\0')
	{
		str_dup[counter] = s1[counter];
		counter++;
	}
	str_dup[counter] = '\0';
	return (str_dup);
}

int	number_of_characters(const char *str)
{
	int	counter;

	counter = 0;
	while (*(str + counter) != '\0')
	{
		counter++;
	}
	return (counter);
}

int	concatenate_strings(int counter, char const *str_origin, char *str_destiny)
{
	int	counter_char;
	int	counter2;

	counter_char = counter;
	counter2 = 0;
	while (*(str_origin + counter2) != '\0')
	{
		*(str_destiny + counter_char) = *(str_origin + counter2);
		counter_char++;
		counter2++;
	}
	return (counter_char);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		total_characters;
	char	*str_space;
	int		counter;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	total_characters = number_of_characters(s1) + number_of_characters(s2) + 1;
	str_space = (char *)malloc(total_characters * sizeof(char));
	if (str_space == NULL)
		return (NULL);
	counter = concatenate_strings(0, s1, str_space);
	counter = concatenate_strings(counter, s2, str_space);
	str_space[counter] = '\0';
	return (str_space);
}
