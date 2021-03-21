/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 02:17:49 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/02/14 16:25:23 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	lit_len;
	size_t	i;

	i = 0;
	lit_len = ft_strlen(little);
	if (*little == '\0')
		return ((char *)big);
	while ((*big != '\0') && (i < len))
	{
		if ((ft_strncmp(big, little, lit_len) == 0) && (i + lit_len <= len))
		{
			return ((char *)big);
		}
		big++;
		i++;
	}
	return (NULL);
}
