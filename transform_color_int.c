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

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

char	*skip_whitespace(char *str)
{
	while (ft_isspace((unsigned char)*str))
		str++;
	return (str);
}

int	get_digit_value(char c)
{
	if (ft_isdigit((unsigned char)c))
		return (c - '0');
	if (ft_isalpha((unsigned char)c))
		return (ft_tolower((unsigned char)c) - 'a' + 10);
	return (-1);
}

uint32_t	ft_strtol(char *str, char **endptr, int base)
{
	uint32_t	result;
	int			digit;

	if (!str || (base != 10 && base != 16))
		return (0);
	str = skip_whitespace(str);
	if (base == 16 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		str += 2;
	result = 0;
	while (*str)
	{
		digit = get_digit_value(*str);
		if (digit < 0 || digit >= base)
			break ;
		result = result * base + digit;
		str++;
	}
	if (endptr)
		*endptr = (char *)str;
	return (result);
}

uint32_t	hex_to_uint32(char *hex)
{
	uint32_t	rgb;
	uint32_t	abgr;

	if (!hex || ft_strlen(hex) != 6)
		return (0xFFFFFFFF);
	rgb = (uint32_t)ft_strtol(hex, NULL, 16);
	abgr = 0xFF000000 | ((rgb & 0xFF) << 16)
		| (rgb & 0xFF00) | ((rgb >> 16) & 0xFF);
	return (abgr);
}
