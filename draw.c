/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:03:50 by frocha            #+#    #+#             */
/*   Updated: 2024/12/04 14:03:51 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

uint32_t	get_color_int(char *color_element)
{
	return (hex_to_uint32(color_element));
}

void	draw_pix(t_fdf *point, int *begin, int *end, char *color)
{
	int	err;
	int	dx;
	int	dy;

	dx = abs(end[0] - begin[0]);
	dy = abs(end[1] - begin[1]);
	err = dx - dy;
	while (!(begin[0] == end[0] && begin[1] == end[1]) && (begin[0] < 1920
			&& begin[1] < 1080) && begin[1] > 0 && begin[0] > 0)
	{
		mlx_put_pixel(point->canvas, begin[0], begin[1], get_color_int(color));
		if (err > 0)
		{
			err -= dy;
			begin[0] += get_steep_sx(&begin[0], &end[0]);
		}
		else
		{
			err += dx;
			begin[1] += get_steep_sy(&begin[1], &end[1]);
		}
	}
}

void	wu_algo(t_fdf *fdf_info, int *begin, int *end)
{
	int	z;
	int	z1;
	int	x;
	int	y;

	x = begin[0];
	y = begin[1];
	z = fdf_info->map_node[begin[1]][begin[0]].z_axis;
	z1 = fdf_info->map_node[end[1]][end[0]].z_axis;
	zoom(fdf_info, begin, end);
	isometric(&begin[0], &begin[1], z);
	isometric(&end[0], &end[1], z1);
	shift(fdf_info, begin, end);
	draw_pix(fdf_info, begin, end, fdf_info->map_node[y][x].color);
}

void	draw_matrix(t_fdf *fdf_info)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf_info->length)
	{
		x = 0;
		while (x < fdf_info->width)
		{
			if (x < fdf_info->width - 1)
				wu_algo(fdf_info, (int []){x, y}, (int []){x + 1, y});
			if (y < fdf_info->length - 1)
				wu_algo(fdf_info, (int []){x, y}, (int []){x, y + 1});
			x++;
		}
		y++;
	}
}
