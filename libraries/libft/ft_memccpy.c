/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 00:01:29 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/19 21:07:59 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char	*dest_cast;
	char	*src_cast;
	char	c_cast;

	dest_cast = (char *)dest;
	src_cast = (char *)src;
	c_cast = (char)c;
	while ((*src_cast != c_cast) && (n > 0))
	{
		*dest_cast = *src_cast;
		dest_cast++;
		src_cast++;
		n--;
	}
	if (*src_cast == c_cast)
	{
		*dest_cast = *src_cast;
		dest_cast++;
		return ((void *)dest_cast);
	}
	return (NULL);
}
