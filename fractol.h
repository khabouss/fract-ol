/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkhabous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 18:58:16 by tkhabous          #+#    #+#             */
/*   Updated: 2021/11/16 19:04:37 by tkhabous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define MAX_IT 100
# define WIDTH 500
# define HEIGHT 500
# define MSG "- Mandelbrot\n- Julia [1,2,3,4]\n"
# include "mlx.h"
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	int				fract_type;
	void			*mlx_id;
	void			*win_id;
	void			*img_id;
	int				*pixels;
	double			zoom;
	double			a;
	double			b;
	int				julia_set;
}				t_vars;

int		fun(int key, int x, int y, t_vars *vars);
int		onclicklistener(int key, t_vars *vars);
int		ft_strcmp(char *str1, char *str2);
int		ft_strlen(char *str);
double	*get_complex(int type);
void	fract(t_vars vars);
t_vars	init_vars(int add);
int		check_args(int argc, char **argv, t_vars *vars);

#endif
