/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkhabous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 18:42:26 by tkhabous          #+#    #+#             */
/*   Updated: 2021/10/30 18:42:27 by tkhabous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"



void			draw_img(t_vars vars, int xcor, int ycor, int color)
{
	if (ycor < HEIGHT && xcor < WIDTH)
		vars.pixels[ycor * WIDTH + xcor] = color;
}


int getJulia(double x, double y, double *c)
{
    int it = 0;
    double z[2];
    double z_s[2];
    
    z[0] = x;
    z[1] = y;
    z_s[0] = (z[0] * z[0]) - (z[1] * z[1]) + c[0];
    z_s[1] = (2 * z[0] * z[1]) + c[1];
    while ((z_s[0]*z_s[0]) + (z_s[1]*z_s[1]) < 4 && it < MAX_IT)
    {
        it++;
        z[0] = z_s[0];
        z[1] = z_s[1];
        z_s[0] = (z[0] * z[0]) - (z[1] * z[1]) + c[0];
        z_s[1] = (2 * z[0] * z[1]) + c[1];
    }
    return (it == MAX_IT) ? 0xffff : (it * 51600)/MAX_IT;
}

int getColor(double x, double y){

    int it = 0;
    double real = 0;
    double img = 0;
    double real_square = (real * real) - (img * img) + x;
    double img_square = (2 * real * img) + y;
    while ((real_square*real_square) + (img_square*img_square) < 4 && it < MAX_IT)
    {
        it++;
        real = real_square;
        img = img_square;

        real_square = (real * real) - (img * img) + x;
        img_square = (2 * real * img) + y;
    }
    return (it == MAX_IT) ? 0xffff : (it * 154800)/MAX_IT;
}

void fract(t_vars vars)
{
    int i=0, j=0;
    double x, y;
    int color;
    double *complex;

    complex = get_complex(vars.julia_set);
    while (i < WIDTH){
        j = 0;
        while (j < HEIGHT)
        {
            x = (((double)i * vars.zoom)/WIDTH) - (vars.zoom/2) + vars.A;
            y = (((double)j * vars.zoom)/HEIGHT) - (vars.zoom/2) + vars.B;
            if (vars.fract_type == 2)
                color = getColor(x, y);
            if (vars.fract_type == 1)
                color = getJulia(x, y, complex);
            draw_img(vars, i, j, color);   
            j++;
        }
        i++;
    }
    free(complex);
}

int main(int argc, char **argv)
{
    int add;
    t_vars	vars;

	add = 0;
    vars.zoom = 4;
    vars.A = 0;
    vars.B = 0;
    vars.mlx_id = mlx_init();
    vars.win_id = mlx_new_window(vars.mlx_id, WIDTH, HEIGHT, "Fract-OL");
	vars.img_id = mlx_new_image(vars.mlx_id, WIDTH, HEIGHT);
	vars.pixels = (int *)mlx_get_data_addr(vars.img_id, &add, &add, &add);
    if (argc != 2 && argc != 3)
        return (printf(MSG));
    if (ft_strcmp(argv[1], "Julia"))
    {
        if (argc != 3 || ft_strlen(argv[2]) != 1 || argv[2][0] >= '9' || argv[2][0] <= '0')
            return (printf(MSG));
        vars.fract_type = 1;
        vars.julia_set = argv[2][0] - 48;
    }
    else if (ft_strcmp(argv[1], "Mandelbrot"))
    {
         if (argc != 2)
            return (printf(MSG));
        vars.fract_type = 2;
    }
    else
        return (printf(MSG));
    mlx_hook(vars.win_id, 2, (1L << 1), onclicklistener, &vars);
    mlx_mouse_hook(vars.win_id, fun, &vars);
    fract(vars);
    mlx_put_image_to_window(vars.mlx_id, vars.win_id, vars.img_id, 0, 0);
	mlx_loop(vars.mlx_id);
    return (1);
}