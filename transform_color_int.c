/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_color_int.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:08:54 by frocha            #+#    #+#             */
/*   Updated: 2024/12/04 14:08:56 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_base_multiplication(int size_str)
{
	int	result;
	int	i;

	i = 0;
	result = 1;
	while (i < size_str)
	{
		result = result * 16;
		i++;
	}
	return (result);
}

int	get_index_hex(char character, int size_str)
{
	char	*hex_values;
	int		i;

	hex_values = "0123456789ABCDEF";
	i = 0;
	while (hex_values[i] != character)
		i++;
	return (i * get_base_multiplication(size_str));
}

int	convert_hex_to_int(char *color_element)
{
	int	i;
	int	result;
	int	size_str;

	i = 2;
	result = 0;
	size_str = ft_strlen(color_element + i) - 1;
	while (color_element[i] != '\0')
	{
		result = result + get_index_hex(color_element[i], size_str);
		i++;
		size_str--;
	}
	return (result);
}

int	get_color_int(char *color_element)
{
	if (color_element && ft_strlen(color_element) > 2)
		return (convert_hex_to_int(color_element));
	return (DEFAULT_COLOR);
}
