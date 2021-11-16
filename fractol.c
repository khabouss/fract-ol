/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkhabous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 18:42:26 by tkhabous          #+#    #+#             */
/*   Updated: 2021/11/16 19:08:04 by tkhabous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_img(t_vars vars, int xcor, int ycor, int color)
{
	if (ycor < HEIGHT && xcor < WIDTH)
		vars.pixels[ycor * WIDTH + xcor] = color;
}

int	get_julia(double x, double y, double *c)
{
	int		it;
	double	z[2];
	double	z_s[2];

	it = 0;
	z[0] = x;
	z[1] = y;
	z_s[0] = (z[0] * z[0]) - (z[1] * z[1]) + c[0];
	z_s[1] = (2 * z[0] * z[1]) + c[1];
	while ((z_s[0] * z_s[0]) + (z_s[1] * z_s[1]) < 4 && it < MAX_IT)
	{
		it++;
		z[0] = z_s[0];
		z[1] = z_s[1];
		z_s[0] = (z[0] * z[0]) - (z[1] * z[1]) + c[0];
		z_s[1] = (2 * z[0] * z[1]) + c[1];
	}
	if (it == MAX_IT)
		return (0xffff);
	else
		return ((it * 51600) / MAX_IT);
}

int	get_mandelbrot(double x, double y)
{
	int		it;
	double	z[2];
	double	z_s[2];

	it = 0;
	z[0] = 0;
	z[1] = 0;
	z_s[0] = (z[0] * z[0]) - (z[1] * z[1]) + x;
	z_s[1] = (2 * z[0] * z[1]) + y;
	while ((z_s[0] * z_s[0]) + (z_s[1] * z_s[1]) < 4 && it < MAX_IT)
	{
		it++;
		z[0] = z_s[0];
		z[1] = z_s[1];
		z_s[0] = (z[0] * z[0]) - (z[1] * z[1]) + x;
		z_s[1] = (2 * z[0] * z[1]) + y;
	}
	if (it == MAX_IT)
		return (0xffff);
	else
		return ((it * 154800) / MAX_IT);
}

void	fract(t_vars vars)
{
	int		i;
	int		j;
	double	cor[2];
	double	*complex;

	i = 0;
	complex = get_complex(vars.julia_set);
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			cor[0] = (((double)i * vars.zoom) / WIDTH)
				- (vars.zoom / 2) + vars.a;
			cor[1] = (((double)j * vars.zoom) / HEIGHT)
				- (vars.zoom / 2) + vars.b;
			if (vars.fract_type == 2)
				draw_img(vars, i, j, get_mandelbrot(cor[0], cor[1]));
			if (vars.fract_type == 1)
				draw_img(vars, i, j, get_julia(cor[0], cor[1], complex));
			j++;
		}
		i++;
	}
	free(complex);
}

int	main(int argc, char **argv)
{
	int		add;
	t_vars	vars;

	add = 0;
	vars = init_vars(add);
	if (!check_args(argc, argv, &vars))
		return (printf(MSG));
	mlx_hook(vars.win_id, 2, (1L << 1), onclicklistener, &vars);
	mlx_mouse_hook(vars.win_id, fun, &vars);
	fract(vars);
	mlx_put_image_to_window(vars.mlx_id, vars.win_id, vars.img_id, 0, 0);
	mlx_loop(vars.mlx_id);
	return (1);
}
