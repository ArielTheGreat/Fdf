/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:48:03 by frocha            #+#    #+#             */
/*   Updated: 2024/11/26 11:48:04 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void set_values_fdf(t_fdf *fdf)
{
	fdf->mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	fdf->canvas = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->zoom = 5;
	fdf->shift_x = 300;
	fdf->shift_y = 300;
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc != 2 || check_file_extension(argv[1]) == 0)
	{
		ft_putendl_fd("Usage: ./fdf <file.fdf>", 2);
		return (EXIT_FAILURE);
	}
	fdf = allocate_memory_and_set_memory(argv[1]);
	if (!fdf || !fdf->map_node)
	{
		ft_putendl_fd("Error: Failed to allocate memory or set matrix dimensions.", 2);
		return (EXIT_FAILURE);
	}
	process_file(argv[1], fdf);
	set_values_fdf(fdf);
	draw_matrix(fdf);
	mlx_image_to_window(fdf->mlx, fdf->canvas, 0, 0);
	mlx_loop_hook(fdf->mlx, &hook, fdf);
	mlx_scroll_hook(fdf->mlx, &mouse_hook, fdf);
	mlx_loop_hook(fdf->mlx, &key_hook, fdf);
	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);
	// free_matrix(array_struct_map, matrix->length + 1);
	// free(fdf);
	return (0);
}
