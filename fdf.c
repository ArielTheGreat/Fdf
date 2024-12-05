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

void	set_values_fdf(t_fdf *fdf)
{
	fdf->mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	fdf->canvas = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->zoom = 5;
	fdf->shift_x = 300;
	fdf->shift_y = 300;
}

void	add_hooks(t_fdf *fdf)
{
	mlx_loop_hook(fdf->mlx, &hook, fdf);
	mlx_scroll_hook(fdf->mlx, &mouse_hook, fdf);
	mlx_loop_hook(fdf->mlx, &key_hook, fdf);
	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);
}

void	free_before_end(t_fdf *fdf)
{
	free_matrix(fdf->map_node, fdf->length);
	free(fdf);
}


int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc != 2 || check_file_extension(argv[1]) == 0)
	{
		system("leaks fdf");
		return (ft_putendl_fd("Usage: ./fdf <file.fdf>", 2), EXIT_FAILURE);
	}
	fdf = allocate_memory_and_set_memory(argv[1]);
	if (!fdf || !fdf->map_node)
		return (system("leaks fdf"), ft_putendl_fd("Err:Failed memory allocation", 2), EXIT_FAILURE);
	process_file(argv[1], fdf);
	set_values_fdf(fdf);
	if (!fdf->mlx)
	{
		ft_putendl_fd("Err: Failed to initialize mlx.", 2);
		system("leaks fdf");
		return (free_before_end(fdf), EXIT_FAILURE);
	}
	draw_matrix(fdf);
	if (mlx_image_to_window(fdf->mlx, fdf->canvas, 0, 0) < 0)
	{
		ft_putendl_fd("Err: Failed to render image to window.", 2);
		mlx_terminate(fdf->mlx);
		system("leaks fdf");
		return (free_before_end(fdf), EXIT_FAILURE);
	}
	add_hooks(fdf);
	free_before_end(fdf);
	system("leaks fdf");
	return (0);
}
