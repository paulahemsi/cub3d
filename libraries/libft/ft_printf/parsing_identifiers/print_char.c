/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:18:16 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/19 20:00:55 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static void	print_c(t_flags *flag, va_list args)
{
	if (*flag->ptr == '%')
		ft_putchar(*flag->ptr);
	else
		ft_putchar((char)va_arg(args, int));
	flag->length++;
}

static void	print_width(t_flags *flag, char padding)
{
	ft_putchar(padding);
	flag->length++;
	flag->min_width--;
}

void	print_char(t_flags *flag, va_list args)
{
	char	padding;

	if ((flag->zero_padding) && (*flag->ptr == '%') && !(flag->left_align))
		padding = '0';
	else
		padding = ' ';
	if (flag->left_align)
		print_c(flag, args);
	while (flag->min_width > 1)
		print_width(flag, padding);
	if (!(flag->left_align))
		print_c(flag, args);
}
