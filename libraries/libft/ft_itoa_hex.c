/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 09:50:17 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/19 20:45:25 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	invert_hex(t_itoa_hex *aux)
{
	int	i;

	i = 0;
	while (i < (aux->length / 2))
	{
		aux->temp = aux->hex[i];
		aux->hex[i] = aux->hex[aux->length - i - 1];
		aux->hex[aux->length - i - 1] = aux->temp;
		i++;
	}
}

static void	convert_to_hex(t_itoa_hex *aux, unsigned long int *number)
{
	while (*number > 0)
	{
		aux->to_hex = *number % 16;
		if (aux->to_hex < 10)
			aux->hex[aux->length] = aux->to_hex + 48;
		else
			aux->hex[aux->length] = aux->to_hex + aux->case_c;
		*number /= 16;
		aux->length++;
	}
}

char	*ft_itoa_hex(unsigned long int number, char case_conversion_char)
{
	t_itoa_hex	aux;

	aux.length = ft_countdigit(number);
	aux.hex = (char *)malloc((aux.length + 1) * sizeof(char));
	if (!(aux.hex))
		return (NULL);
	if (case_conversion_char == 'X')
		aux.case_c = 55;
	else
		aux.case_c = 87;
	if (number == 0)
	{
		aux.hex[0] = '0';
		aux.hex[1] = '\0';
		return (aux.hex);
	}
	aux.length = 0;
	convert_to_hex(&aux, &number);
	aux.hex[aux.length] = '\0';
	aux.length = ft_strlen(aux.hex);
	invert_hex(&aux);
	return (aux.hex);
}
