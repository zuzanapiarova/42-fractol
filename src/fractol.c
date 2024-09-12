/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:43:21 by zpiarova          #+#    #+#             */
/*   Updated: 2024/09/12 19:27:44 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

// clone MLX42: git clone https://github.com/codam-coding-college/MLX42.git

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
// and color it dependeing on how many iterations it took for point to escape
// leave white if point did not escape in fractal.iterations num of iterations
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
			return (mlx_put_pixel(f.img, x, y, set_color(i, f.colorway)));
		i++;
	}
	mlx_put_pixel(f.img, x, y, f.inside);
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
	f->iters = 15;
	f->escape_value = 8;
	f->colorway = "multi";
	f->inside = P;
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
