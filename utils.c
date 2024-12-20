/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:00:44 by frocha            #+#    #+#             */
/*   Updated: 2024/12/04 14:00:46 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric(int *x, int *y, int z)
{
	*x = (*x - *y) * cos(0.5265);
	*y = (*x + *y) * sin(0.5265) - z;
}

void	zoom(t_fdf *point, int *begin, int *end)
{
	begin[0] *= point->zoom;
	begin[1] *= point->zoom;
	end[0] *= point->zoom;
	end[1] *= point->zoom;
}

void	shift(t_fdf *point, int *begin, int *end)
{
	begin[0] += (point)->shift_x;
	end[0] += (point)->shift_x;
	begin[1] += (point)->shift_y;
	end[1] += (point)->shift_y;
}

int	get_steep_sx(int *x, int *x1)
{
	if (*x < *x1)
		return (1);
	else
		return (-1);
}

int	get_steep_sy(int *y, int *y1)
{
	if (*y < *y1)
		return (1);
	else
		return (-1);
}
