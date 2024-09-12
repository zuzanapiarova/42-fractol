/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:56:45 by zpiarova          #+#    #+#             */
/*   Updated: 2024/09/12 18:47:00 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	if (s1 == NULL || s2 == NULL || n <= 0)
		return (0);
	while (*s1 == *s2 && n != 0 && *s1 != 0)
	{
		s1++;
		s2++;
		n--;
	}
	return (*s1 - *s2);
}

double	atod(char *str)
{
	long	in;
	double	d;
	double	pow;
	int		sign;

	in = 0;
	d = 0;
	pow = 1;
	sign = 1;
	while (*str == 32 || *str == '+' || *str == '-')
	{
		if (*str++ == '-')
			sign *= -1;
	}
	while (*str >= '0' && *str <= '9')
		in = in * 10 + (*str++ - '0');
	if (*str == '.' || *str == ',')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		pow = pow / 10;
		d = d + ((*str++ - '0') * pow);
	}
	return ((in + d) * sign);
}

// void	malloc_error(void)
// {
// 	perror("Memory allocation failed. Exiting now.");
// 	exit(EXIT_FAILURE);
// }

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	set_color(int i, char *color)
{
	int	palette[COLORWAY_SIZE];

	palette[0] = A1;
	palette[1] = A2;
	palette[2] = A3;
	palette[3] = A5;
	palette[4] = A6;
	palette[5] = A7;
	palette[6] = A8;
	palette[7] = A9;
	palette[8] = A0;
	if (!ft_strncmp(color, "blue", 4))
	{
		palette[0] = BA;
		palette[1] = BB;
		palette[2] = BC;
		palette[3] = BE;
		palette[4] = BF;
		palette[5] = BG;
		palette[6] = BH;
		palette[7] = BI;
		palette[8] = BJ;
	}
	return (palette[i % COLORWAY_SIZE]);
}
