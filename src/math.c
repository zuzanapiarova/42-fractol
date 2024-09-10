/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:43:58 by zpiarova          #+#    #+#             */
/*   Updated: 2024/08/06 20:47:11 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

//function to calculate how many iterations i need to know if the point escaped
//so it is black(inside) or color(outside )
/* explanation: the less iterations there are we cannot be sure that
   the point escapes or not - so in few iterations the point is black
   as it has not escaped yet so it seems stable for now, the more iterations
   we add the more points escape and the image becomes more and more precise
   so in less iterations the mandelbrot looks like a big blob, in more
   iterations it is refines into smaller and more precise shape
*/

// linear interpolation function = maps/scales points proportionate and
// linearly to other points to keep the proportions but scaled in/out
double	scale(double num, double new_min, double new_max, double old_max)
{
	return ((new_max - new_min) * (num) / ((old_max)) + new_min);
}

// mandelbrot math:
// point is in mandelbrot if z = z^2 + c
// z and c are both complex numbers - both have a real and an imaginary part
// initially - in the first iteration: z is 0,
// c is the actual pixel in window with its passed x and y coordinates
// we can illustrate the real value as value at x axis
// and imaginary value(without the i) as value at the y axis
// this function does the operation z = z^2 + c
// squaring complex number - z^2
// math: complex number is basically : cnum(real) + cnum(imaginary)
// --> rnum + inum --> rnum + inum*i
// so squaring cnum^2 = (cnum(real) + cnum(imaginary))^2 is:
// cnum(real)^2 + 2*cnum(real)*cnum(imaginary) + cnum(imaginary)^2
//    cnum^2 = (rnum + inum*i)^2 = rnum^2 + 2*rnum*inum*i + inum^2*i^2
// but i^2 is -1 so this imaginary component turns into real component
// and only imaginary number left is 2*rnum*inum*i
// --> cnum^2 = rnum^2 - inum^2 + 2*rnum*inum*i
//             |------real-----| |--imaginary--|
// --> we get new real and new imaginary parts
// last 2 lines before return are adding two complex numbers - z^2 + c
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
