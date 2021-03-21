/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 23:32:38 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/02/11 00:09:04 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*pointer;

	if (!(pointer = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	pointer->content = content;
	pointer->next = NULL;
	return (pointer);
}
