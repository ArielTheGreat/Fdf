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

#include <stdint.h>
#include <stddef.h>
#include <ctype.h>
#include <errno.h>

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || 
			c == '\v' || c == '\f' || c == '\r');
}

uint32_t	ft_strtol(const char *str, char **endptr, int base)
{
	uint32_t	result;
	int			digit;

	if (!str || (base != 10 && base != 16))
	{
		return (0);
	}
	while (ft_isspace((unsigned char)*str))
		str++;
	if (base == 16 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		str += 2;

	result = 0;
	while (*str)
	{
		if (ft_isdigit((unsigned char)*str))
			digit = *str - '0';
		else if (ft_isalpha((unsigned char)*str))
			digit = ft_tolower((unsigned char)*str) - 'a' + 10;
		else
			break;
		if (digit >= base)
			break;
		result = result * base + digit;
		str++;
	}
	if (endptr)
		*endptr = (char *)str;
	return (result);
}


uint32_t	hex_to_uint32(const char *hex)
{
	uint32_t	rgb;
	uint32_t	abgr;

	if (!hex || ft_strlen(hex) != 6)
		return (0xFFFFFFFF);

	rgb = (uint32_t)ft_strtol(hex, NULL, 16);

	abgr = 0xFF000000 | ((rgb & 0xFF) << 16) | (rgb & 0xFF00) | ((rgb >> 16) & 0xFF);

	return (abgr);
}

uint32_t	get_color_int(char *color_element)
{
	return (hex_to_uint32(color_element));
}
