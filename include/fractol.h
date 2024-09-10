/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:43:40 by zpiarova          #+#    #+#             */
/*   Updated: 2024/09/10 19:53:22 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>	// malloc free
# include <unistd.h>	// write
# include <stdio.h>	// printf
# include <math.h>	// math functions
# include "../MLX42/include/MLX42/MLX42.h" //minilibx

# define HEIGHT	1000
# define WIDTH	1000
# define W 0xffffffff
# define B 0x000000ff
# define A 0x01ffffff
# define R 0xd91116ff
# define Y 0xfff700ff
# define P 0xc457edff

typedef struct s_fractal
{
	void		*fractal;
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
