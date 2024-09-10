/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:43:21 by zpiarova          #+#    #+#             */
/*   Updated: 2024/09/10 19:54:04 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

// ADDING MLX42:
// git clone https://github.com/codam-coding-college/MLX42
// cd MLX42
// cmake -B build
// make -C build/

// CALL THE PROGRAM: ./fractol(=arg[0]) mandelbrot(=arg[1])   ==>  argc is 2
// we are basically just setting color to each pixel based on how many
// iterations it takes for point with that coordinates to escape to infinity
// points that are inside the mandelbrot set are white - never escape
// points that are outside based on their color we can tell how many
// iterations it takes for them to escape

// Exit the program when given wrong input
static void	ft_error(void)
{
	ft_putstr_fd("Fractals available for exploration:"
		"\n\tMandelbrot\n\tJulia <real> <imaginary> //best between (-1,1)\n\t"
		"Please specify the name and in case of Julia "
		"parameters as arguments to the program.\nExiting now.", 1);
	exit(EXIT_FAILURE);
}

// for each pixel we perform the mandelbrot set function z = z^2 + c
// for the first run of the function, we set z real and imaginary values to 0
// because z=0 is the beginning condition for mandelbrot set
// c real value is our real x position from 0 and c imaginary value is our y position from 0
// we need to scale the x and y points because the x and y coordinates start at 0 and end at WIDTH/HEIGHT
// but our mandelbrot image has dimensions x(-2.2, 0.8) and y(1.2, -1.8)
// we color it dependeing on how many iterations it took for point to escape
// leave white if did not escape in fractal.iterations number of iterations
void	set_pixel(int x, int y, t_fractal f)
{
	t_complex	z;
	t_complex	c;
	int			i;

	z.real = 0;
	z.imaginary = 0;
	c.real = scale(x, f.xstart, f.xend, WIDTH);
	c.imaginary = scale(y, f.ystart, f.yend, HEIGHT);
	if (!ft_strncmp(f.name, "julia", 5))
	{
		z.real = (scale(x, f.xstart, f.xend, WIDTH));
		z.imaginary = (scale(y, f.ystart, f.yend, HEIGHT));
		c.real = f.julia_r;
		c.imaginary = f.julia_i;
	}
	i = 0;
	while (i < f.iters)
	{
		z = complex_operation(z, c);
		if (pow(z.real, 2) + pow(z.imaginary, 2) > f.escape_value)
			return (mlx_put_pixel(f.img, x, y, scale(i, A, B, f.iters)));
		i++;
	}
	mlx_put_pixel(f.img, x, y, B);
}

// iterates through window pixels one by one, each pixel in each row,
// to set its color based on whether it escaped and in how many iteration
void	render_window(t_fractal fractal)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			set_pixel(x, y, fractal);
	}
}

// initialize the fractal struct with the initial data
void	fractal_init(t_fractal *f, char *name)
{
	f->name = name;
	f->iters = 10;
	f->escape_value = 4;
	f->xstart = -2.2;
	f->xend = 0.8;
	f->ystart = 1.2;
	f->yend = -1.8;
	f->window = mlx_init(WIDTH, HEIGHT, f->name, false);
	if (!f->window)
	{
		mlx_close_window(f->window);
		mlx_terminate(f->window);
		exit(EXIT_FAILURE);
	}
	f->img = mlx_new_image(f->window, WIDTH, HEIGHT);
	if (!f->img || (mlx_image_to_window(f->window, f->img, 0, 0) < 0))
	{
		mlx_close_window(f->window);
		mlx_terminate(f->window);
		exit(EXIT_FAILURE);
	}
}

int32_t	main(int argc, char *argv[])
{
	t_fractal	fractal;

	if ((argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10))
		|| (argc >= 4 && !ft_strncmp(argv[1], "julia", 5)))
	{
		fractal_init(&fractal, argv[1]);
		if (argv[2] && argv[3])
		{
			fractal.julia_r = atod(argv[2]);
			fractal.julia_i = atod(argv[3]);
		}
		render_window(fractal);
		mlx_key_hook(fractal.window, &my_keyhook, &fractal);
		mlx_scroll_hook(fractal.window, &my_scrollhook, &fractal);
		mlx_close_hook(fractal.window, &my_closehook, &fractal);
		mlx_loop(fractal.window);
		mlx_close_window(fractal.window);
		mlx_terminate(fractal.window);
		return (EXIT_SUCCESS);
	}
	else
		ft_error();
	return (0);
}

// TODO:
// check memory leaks
// check that .o files and program are removed
// sierpinski
// color range shift with some keys
