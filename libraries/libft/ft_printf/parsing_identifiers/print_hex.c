/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 23:34:03 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/19 20:03:47 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static void	print_precision(t_flags *flag, int precision)
{
	while (precision > 0)
	{
		ft_putchar('0');
		flag->length++;
		precision--;
	}
}

static void	print_pointer_prefix(t_flags *flag)
{
	if (*flag->ptr == POINTER)
	{
		ft_putstr("0x");
		flag->length += 2;
	}
}

static void	print_width(t_flags *flag, int hex_len, char *hex)
{
	char	c;
	int		prefix_len;
	int		limit;

	prefix_len = 0;
	c = ' ';
	if (*flag->ptr == POINTER)
		prefix_len = 2;
	if ((flag->zero_padding) && (flag->precision < 0) && !(flag->left_align))
		c = '0';
	if (flag->precision > (hex_len + prefix_len))
		limit = flag->precision;
	else if ((flag->precision) || (*hex != '0'))
		limit = (hex_len + prefix_len);
	else
		limit = prefix_len;
	while (flag->min_width > limit)
	{
		ft_putchar(c);
		flag->length++;
		flag->min_width--;
	}
}

static void	print_h(t_flags *flag, char **hex)
{
	int		hex_len;

	hex_len = ft_strlen(*hex);
	if (!(flag->left_align))
		print_width(flag, hex_len, *hex);
	print_pointer_prefix(flag);
	print_precision(flag, (flag->precision - hex_len));
	if (**hex != '0' || flag->precision != 0)
	{
		ft_putstr(*hex);
		flag->length += hex_len;
	}
	if (flag->left_align)
		print_width(flag, hex_len, *hex);
}

int	print_hex(t_flags *flag, va_list args)
{
	char	*hex;
	char	char_case;

	if (*flag->ptr == POINTER)
	{
		char_case = 'x';
		hex = ft_itoa_hex(va_arg(args, unsigned long int), char_case);
	}
	else
	{
		char_case = *flag->ptr;
		hex = ft_itoa_hex(va_arg(args, unsigned int), char_case);
	}
	if (hex == NULL)
		return (ERROR);
	print_h(flag, &hex);
	free(hex);
	return (1);
}
