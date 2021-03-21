/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 03:10:57 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/02/08 20:59:54 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_cast;
	unsigned char	*src_cast;
	size_t			i;

	i = 0;
	dest_cast = (unsigned char *)dest;
	src_cast = (unsigned char *)src;
	if (dest_cast == src_cast)
		return (dest_cast);
	if ((src_cast < dest_cast) && ((src_cast + n) > dest_cast))
		while (i++ < n)
			dest_cast[n - i] = src_cast[n - i];
	else if ((src_cast > dest_cast) && ((dest_cast + n) > src_cast))
	{
		while (i < n)
		{
			dest_cast[i] = src_cast[i];
			i++;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
