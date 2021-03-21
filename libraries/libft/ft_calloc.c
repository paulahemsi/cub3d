/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 16:58:28 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/02/09 21:26:28 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	*pointer;
	size_t	total_size;

	total_size = nmemb * size;
	if ((total_size) > INT_MAX)
	{
		return (NULL);
	}
	if (!(pointer = malloc(total_size)))
	{
		return (NULL);
	}
	ft_memset(pointer, 0, total_size);
	return ((void *)pointer);
}
