/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 11:36:00 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/19 19:43:38 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s, char const *set)
{
	size_t	end;
	size_t	length;

	if (!s || !set)
		return (0);
	while ((*s) && (ft_strchr(set, *s)))
	{
		s++;
	}
	end = ft_strlen(s);
	while ((end) && (ft_strchr(set, s[end])))
	{
		end--;
	}
	length = end + 1;
	return (ft_substr(s, 0, length));
}
