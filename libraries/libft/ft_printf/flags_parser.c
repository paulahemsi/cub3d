/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 15:11:09 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/19 19:59:55 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	identifier_parser(t_flags *flag, va_list args, char **initial_ptr)
{
	if ((*flag->ptr == 'c') || (*flag->ptr == '%'))
		print_char(flag, args);
	else if (*flag->ptr == 's')
	{
		if (print_string(flag, args) == ERROR)
			return (ERROR);
	}
	else if (*flag->ptr == 'd' || *flag->ptr == 'i' || *flag->ptr == 'u')
		print_integer(flag, args);
	else if (*flag->ptr == 'x' || *flag->ptr == 'X' || *flag->ptr == 'p')
	{
		if (print_hex(flag, args) == ERROR)
			return (ERROR);
	}
	else
	{
		ft_putchar(**initial_ptr);
		flag->length++;
		flag->ptr = *initial_ptr;
	}
	return (1);
}

static void	update_width(t_flags *flag, va_list args)
{
	if (*flag->ptr == '*')
	{
		flag->min_width = va_arg(args, int);
		if (flag->min_width < 0)
		{
			flag->left_align = TRUE;
			flag->min_width *= -1;
		}
		flag->ptr++;
	}
	else
	{
		flag->min_width = ft_atoi(flag->ptr);
		flag->ptr += ft_numlen(flag->min_width);
	}
}

static void	update_precision(t_flags *flag, va_list args)
{
	flag->ptr++;
	if (*flag->ptr == '*')
	{
		flag->precision = va_arg(args, int);
		flag->ptr++;
	}
	else if (ft_isdigit(*flag->ptr))
	{
		while (ft_isdigit(*flag->ptr))
		{
			flag->precision = ft_atoi(flag->ptr);
			flag->ptr += ft_numlen(flag->precision);
		}
	}
	else
		flag->precision = 0;
	if ((flag->precision >= 0) && (*flag->ptr != '%'))
		flag->zero_padding = FALSE;
}

static void	update_flags(t_flags *flag, va_list args)
{
	while (ft_strchr("-0", *flag->ptr))
	{
		if (*flag->ptr == '-')
			flag->left_align = TRUE;
		if (*flag->ptr == '0')
			flag->zero_padding = TRUE;
		flag->ptr++;
	}
	if (ft_isdigit(*flag->ptr) || *flag->ptr == '*')
		update_width(flag, args);
	if (*flag->ptr == '.')
		update_precision(flag, args);
}

size_t	flags_parser(char **ptr, va_list args, size_t length)
{
	t_flags	flag;
	char	*initial_ptr;

	initial_ptr = *ptr;
	ft_memset(&flag, FALSE, sizeof(flag));
	flag.precision = -1;
	flag.length = length;
	flag.ptr = *ptr + 1;
	update_flags(&flag, args);
	if ((ft_isalpha(*flag.ptr)) || *flag.ptr == '%')
	{
		if (identifier_parser(&flag, args, &initial_ptr) == ERROR)
			return (ERROR);
	}
	else
	{
		ft_putchar(*initial_ptr);
		flag.length++;
		flag.ptr = initial_ptr;
	}
	flag.ptr++;
	*ptr = flag.ptr;
	return (flag.length);
}
