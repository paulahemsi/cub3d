/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 23:51:11 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/19 20:49:26 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	itoa_isnegative(int number)
{
	if (number < 0)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

static int	itoa_countdigit(unsigned int number)
{
	size_t	digits;

	if (number == 0)
	{
		return (1);
	}
	digits = 0;
	while (number >= 1)
	{
		number /= 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	char			*string;
	unsigned int	neg;
	unsigned int	number;
	unsigned int	digits;

	neg = itoa_isnegative(n);
	if (neg)
		number = -n;
	else
		number = n;
	digits = itoa_countdigit(number);
	string = (char *)malloc(digits + neg + 1);
	if (!(string))
		return (NULL);
	if (neg == 1)
		string[0] = '-';
	string[digits + neg] = '\0';
	while (digits > 0)
	{
		string[(digits - 1) + neg] = (number % 10) + '0';
		number /= 10;
		digits--;
	}
	return (string);
}
