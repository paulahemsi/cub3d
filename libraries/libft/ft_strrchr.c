/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 02:16:31 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/02/14 20:50:53 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char		*c_in_s;
	const char	*str_init;

	if (c > 127)
		c %= 256;
	str_init = str;
	while (*str != '\0')
		str++;
	while (str != str_init)
	{
		if (*str == c)
		{
			c_in_s = (char *)str;
			return (c_in_s);
		}
		str--;
	}
	if (*str == c)
	{
		c_in_s = (char *)str;
		return (c_in_s);
	}
	return (NULL);
}
