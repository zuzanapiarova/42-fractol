/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:47:17 by zpiarova          #+#    #+#             */
/*   Updated: 2024/09/10 19:11:58 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

// ----- HOOKS ------
// listen for keypress events for ESC, arrows, plus, minus, AWDS for Julia

void	aswd_hook(mlx_key_data_t keydata, t_fractal *f)
{
	if (keydata.key == MLX_KEY_A && keydata.action == 0)
		f->julia_r -= 0.01;
	else if (keydata.key == MLX_KEY_D && keydata.action == 0)
		f->julia_r += 0.01;
	else if (keydata.key == MLX_KEY_W && keydata.action == 0)
		f->julia_i -= 0.01;
	else if (keydata.key == MLX_KEY_S && keydata.action == 0)
		f->julia_i += 0.01;
}

void	arrows_hook(mlx_key_data_t keydata, t_fractal *f)
{
	f->diff = f->xend - f->xstart;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == 0)
	{
		f->xstart += f->diff / 5;
		f->xend += f->diff / 5;
	}
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == 0)
	{
		f->xstart -= f->diff / 5;
		f->xend -= f->diff / 5;
	}
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == 0)
	{
		f->ystart -= f->diff / 5;
		f->yend -= f->diff / 5;
	}
	else if (keydata.key == MLX_KEY_UP && keydata.action == 0)
	{
		f->ystart += f->diff / 5;
		f->yend += f->diff / 5;
	}
}
// we create t_fractal type inside and assign it to point to our fractal
// because this functions accept only void pointers, not of type t_fractal
void	my_keyhook(mlx_key_data_t keydata, void *fractal)
{
	t_fractal	*f;

	f = (t_fractal *)fractal;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == 0)
	{
		mlx_close_window(f->window);
		mlx_terminate(f->window);
		exit(1);
	}
	else if (keydata.key == MLX_KEY_KP_ADD && keydata.action == 0)
		f->iters += 5;
	else if ((keydata.key == MLX_KEY_MINUS
			|| keydata.key == MLX_KEY_KP_SUBTRACT)
		&& keydata.action == 0)
		f->iters -= 5;
	arrows_hook(keydata, f);
	aswd_hook(keydata, f);
	render_window(*f);
}

// scroll on mouse movement, when ydelta < 0 zoom in, when ydelta > 0 zoom out
void	my_scrollhook(double xdelta, double ydelta, void *fractal)
{
	t_fractal	*f;
	double		diff;

	f = (t_fractal *)fractal;
	diff = (f->yend - f->ystart);
	if (ydelta < 0 && !xdelta)
	{
		f->ystart -= 0.1 * diff;
		f->yend += 0.1 * diff;
		f->xstart += 0.1 * diff;
		f->xend -= 0.1 * diff;
	}
	if (ydelta > 0 && !xdelta)
	{
		f->ystart += 0.1 * diff;
		f->yend -= 0.1 * diff;
		f->xstart -= 0.1 * diff;
		f->xend += 0.1 * diff;
	}
	render_window(*f);
}

void	my_closehook(void *fractal)
{
	t_fractal	*f;

	f = (t_fractal *)fractal;
	mlx_close_window(f->window);
	mlx_terminate(f->window);
	exit(1);
}
