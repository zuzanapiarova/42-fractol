/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:43:58 by zpiarova          #+#    #+#             */
/*   Updated: 2024/09/12 19:17:44 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

// linear interpolation function = maps/scales points proportionate and
// linearly to other points to keep the proportions but scaled in/out
double	scale(double num, double new_min, double new_max, double old_max)
{
	return ((new_max - new_min) * (num) / ((old_max)) + new_min);
}

// performs the function  = z^2 + c for when z, c are complex numbers
t_complex	complex_operation(t_complex z, t_complex c)
{
	t_complex	z_squared;
	t_complex	result;

	z_squared.real = pow(z.real, 2) - pow(z.imaginary, 2);
	z_squared.imaginary = 2 * z.real * z.imaginary;
	result.real = z_squared.real + c.real;
	result.imaginary = z_squared.imaginary + c.imaginary;
	return (result);
}
