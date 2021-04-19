/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 22:05:05 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/19 20:45:51 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_numlen(int number)
{
	size_t	digits;

	digits = 0;
	if (number == 0)
		return (1);
	else if (number < 0)
	{
		digits++;
		number *= -1;
	}
	while (number >= 1)
	{
		number /= 10;
		digits++;
	}
	return (digits);
}
