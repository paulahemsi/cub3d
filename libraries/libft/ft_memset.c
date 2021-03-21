/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 22:26:24 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/02/15 12:36:18 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	cc;
	char	*pointer_aux;

	i = 0;
	cc = (char)c;
	pointer_aux = (char *)s;
	while (i < n)
	{
		pointer_aux[i] = cc;
		i++;
	}
	return ((void *)s);
}
