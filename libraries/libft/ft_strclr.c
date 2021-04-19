/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 11:31:39 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/19 21:38:38 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strclr(char *s)
{
	size_t	length;
	size_t	i;

	if (!s)
		return ;
	length = ft_strlen(s);
	i = 0;
	while (i < length)
	{
		s[i] = '\0';
		i++;
	}
}
