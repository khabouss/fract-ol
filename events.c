#include "fractol.h"


int fun(int key ,int x, int y, t_vars *vars)
{
    x = x + 1 - 1;
    y = y + 1 - 1;
    if (key == 5 || key == 4)
    {
        if (key == 5)
            vars->zoom -= 0.1*vars->zoom;
        else
            vars->zoom += 0.1*vars->zoom;
        mlx_clear_window(vars->mlx_id, vars->win_id);
        fract(*vars);
        mlx_put_image_to_window(vars->mlx_id, vars->win_id, vars->img_id, 0, 0);
    }
    return 0;
}

int		onclicklistener(int key, t_vars *vars)
{
    if (key == 123)
        vars->A-=0.05*vars->zoom;
    if (key == 126)
        vars->B-=0.05*vars->zoom;
    if (key == 124)
        vars->A+=0.05*vars->zoom;
    if (key == 125)
        vars->B+=0.05*vars->zoom;
    if (key == 53)
        exit(0);
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

double *get_complex(int type)
{
    double *complex;
    
    complex = (double *)malloc(sizeof(double)*2);
    if (type == 1)
    {
        complex[0] = -0.4;
        complex[1] = 0.6;
    }
    if (type == 2)
    {
        complex[0] = 0.285;
        complex[1] = 0;
    }
    if (type == 3)
    {
        complex[0] = 0;
        complex[1] = -0.8;
    }
    if (type == 4)
    {
        complex[0] = 1 - 1.618033988749;
        complex[1] = 0;
    }
    return complex;
}
