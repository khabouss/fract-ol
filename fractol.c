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

typedef struct	s_vars {
	void            *mlx;
	void	        *win;
    int             fract_type;
    void			*mlx_id;
    void			*win_id;
    void			*img_id;
    int				*pixels;
    double          zoom;
    double          A;
    double          B;
    int            julia_set;
}				t_vars;

void			draw_img(t_vars vars, int xcor, int ycor, int color)
{
	if (ycor < HEIGHT && xcor < WIDTH)
		vars.pixels[ycor * WIDTH + xcor] = color;
}


int getJulia(double x, double y){

    int it = 0;
    int max_it = 50;
    double cx = -0.4;
    double cy = 0.6;
    double real = x;
    double img = y;
    double real_square = (real * real) - (img * img) + cx;
    double img_square = (2 * real * img) + cy;
    while ((real_square*real_square) + (img_square*img_square) < 4 && it < max_it)
    {
        it++;
        real = real_square;
        img = img_square;

        real_square = (real * real) - (img * img) + cx;
        img_square = (2 * real * img) + cy;
    }
    return (it == max_it) ? 0xffff : (it * 51600)/max_it;
}

int getColor(double x, double y){

    int it = 0;
    int max_it = 100;
    double real = 0;
    double img = 0;
    double real_square = (real * real) - (img * img) + x;
    double img_square = (2 * real * img) + y;
    while ((real_square*real_square) + (img_square*img_square) < 4 && it < max_it)
    {
        it++;
        real = real_square;
        img = img_square;

        real_square = (real * real) - (img * img) + x;
        img_square = (2 * real * img) + y;
    }
    return (it == max_it) ? 0xffff : (it * 154800)/max_it;
}

void fract(t_vars vars)
{
    int i=0, j=0;
    double x, y;
    int color;

    while (i < WIDTH){
        j = 0;
        while (j < HEIGHT)
        {
            x = (((double)i * vars.zoom)/WIDTH) - (vars.zoom/2) + vars.A;
            y = (((double)j * vars.zoom)/HEIGHT) - (vars.zoom/2) + vars.B;
            if (vars.fract_type == 2)
                color = getColor(x, y);
            if (vars.fract_type == 1)
                color = getJulia(x, y);
            draw_img(vars, i, j, color);   
            j++;
        }
        i++;
    }
    
}

int		onclicklistener(int key, t_vars *vars)
{
    if (key == 6)
        vars->zoom -= 0.1*vars->zoom;
    if (key == 31)
        vars->zoom += 0.1*vars->zoom;
    if (key == 123)
        vars->A-=0.05*vars->zoom;
    if (key == 126)
        vars->B-=0.05*vars->zoom;
    if (key == 124)
        vars->A+=0.05*vars->zoom;
    if (key == 125)
        vars->B+=0.05*vars->zoom;

    mlx_clear_window(vars->mlx_id, vars->win_id);
    fract(*vars);
    mlx_put_image_to_window(vars->mlx_id, vars->win_id, vars->img_id, 0, 0);
	return (1);
}

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}
int ft_strcmp(char *str1, char *str2)
{
    int i = 0;

    if (ft_strlen(str1) != ft_strlen(str2))
        return (0);
    while (str1[i] != '\0')
    {
        if (str1[i] != str2[i])
            return (0);
        i++;
    }
    return (1);
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
    fract(vars);
    mlx_put_image_to_window(vars.mlx_id, vars.win_id, vars.img_id, 0, 0);
	mlx_loop(vars.mlx_id);
    return (1);
}