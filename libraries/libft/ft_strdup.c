/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 11:21:33 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/03/13 18:43:39 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*string;
	size_t	length;
	size_t	i;

	if (!s)
		return (NULL);
	length = ft_strlen(s);
	string = (char *)malloc(length + 1);
	if (string == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		string[i] = s[i];
		i++;
	}
	string[length] = '\0';
	return (string);
}
