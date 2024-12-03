
# include "fdf.h"

void	clear_window(t_fdf *point)
{
	mlx_delete_image(point -> mlx, point -> canvas);
	point -> canvas = mlx_new_image(point -> mlx, 1920, 1080);
	mlx_image_to_window(point -> mlx, point -> canvas, 0, 0);
}

void	hook(void *param)
{
	t_fdf	*mlx;

	mlx = (t_fdf *)param;
	if (mlx_is_key_down(mlx -> mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx -> mlx);
}

void mouse_hook(double xdelta, double ydelta, void *param)
{
    t_fdf *point;

    xdelta = 0;
    point = (t_fdf *)param;
    if (ydelta > 0)
        point->zoom += 1;
    else if (ydelta < 0)
        point->zoom -= 1;

    if (point->zoom < 1)
        point->zoom = 1;

    clear_window(point);
    draw_matrix(point);
}

void	key_hook(void *param)
{
	t_fdf	*point;

	point = (t_fdf *)param;
	if (mlx_is_key_down(point -> mlx, MLX_KEY_UP))
		point -> shift_y += 10;
	if (mlx_is_key_down(point -> mlx, MLX_KEY_DOWN))
		point -> shift_y -= 10;
	if (mlx_is_key_down(point -> mlx, MLX_KEY_RIGHT))
		point -> shift_x -= 10;
	if (mlx_is_key_down(point -> mlx, MLX_KEY_LEFT))
		point -> shift_x += 10;

	clear_window(point);
	draw_matrix(point);
}