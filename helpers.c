/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkhabous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 18:55:42 by tkhabous          #+#    #+#             */
/*   Updated: 2021/11/16 18:58:02 by tkhabous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_vars	init_vars(int add)
{
	t_vars	vars;

	vars.zoom = 4;
	vars.a = 0;
	vars.b = 0;
	vars.mlx_id = mlx_init();
	vars.win_id = mlx_new_window(vars.mlx_id, WIDTH, HEIGHT, "Fract-OL");
	vars.img_id = mlx_new_image(vars.mlx_id, WIDTH, HEIGHT);
	vars.pixels = (int *)mlx_get_data_addr(vars.img_id, &add, &add, &add);
	return (vars);
}

int	check_args(int argc, char **argv, t_vars *vars)
{
	if (argc != 2 && argc != 3)
		return (0);
	if (ft_strcmp(argv[1], "Julia"))
	{
		if (argc != 3 || ft_strlen(argv[2]) != 1
			|| argv[2][0] >= '5' || argv[2][0] <= '0')
			return (0);
		vars->fract_type = 1;
		vars->julia_set = argv[2][0] - 48;
	}
	else if (ft_strcmp(argv[1], "Mandelbrot"))
	{
		if (argc != 2)
			return (0);
		vars->fract_type = 2;
	}
	else
		return (0);
	return (1);
}
