/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:43:40 by zpiarova          #+#    #+#             */
/*   Updated: 2024/09/11 23:29:40 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>	// malloc free
# include <unistd.h>	// write
# include <stdio.h>	// printf
# include <math.h>	// math functions
# include "../MLX42/include/MLX42/MLX42.h" //minilibx

// preprocessor macros
# define HEIGHT	1000
# define WIDTH	1000
# define W 0xffffffff
# define B 0x000000ff
# define A 0x01ffffff
# define R 0xd91116ff
# define Y 0xfff700ff
# define P 0xc457edff
# define BA 0x00264Dff
# define BB 0x003366ff
# define BC 0x004080ff
# define BD 0x004C99ff
# define BE 0x0059B3ff
# define BF 0x0066CCff
# define BG 0x0073E6ff
# define BH 0x0080FFff
# define BI 0x3399FFff
# define BJ 0x66B2FFff
#define A1 0xFF00FFFF
#define A2 0xFF0066FF
#define A3 0xFF3300FF
#define A4 0xFF6600FF
#define A5 0xFF9900FF
#define A6 0xFFCC00FF
#define A7 0xCCFF00FF
#define A8 0x66FF00FF
#define A9 0x00FF66FF
#define A0 0x00FFFFFF

typedef struct s_fractal
{
	mlx_t		*window;
	mlx_image_t	*img;
	char		*name;
	double		escape_value;
	int			iters;
	double		xstart;
	double		xend;
	double		ystart;
	double		yend;
	double		julia_r;
	double		julia_i;
	double		diff;
}				t_fractal;

typedef struct s_complex
{
	double		real;
	double		imaginary;
}				t_complex;

// main logic
void		render_window(t_fractal fractal);
// hooks
void		my_keyhook(mlx_key_data_t keydata, void *fractal);
void		my_scrollhook(double xdelta, double ydelta, void *fractal);
void		my_closehook(void *fractal);
// utils
int			ft_strncmp(char *s1, char *s2, int n);
double		atod(char *str);
void		ft_putstr_fd(char *s, int fd);
// math
double		scale(double num, double new_min, double new_max, double old_max);
t_complex	complex_operation(t_complex z, t_complex c);

#endif
