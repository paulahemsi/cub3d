/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 00:46:13 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/10 14:57:20 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	return_error(int error_id)
{
	if (error_id == -1)
		ft_putstr("Error\nUsage: cub3d file.cub (--save)\n");
	else if (error_id == -2)
		ft_putstr("Error\nNot a valid file\n");
	else if (error_id == -3)
		ft_putstr("Error\ninvalid path\n");
	else if (error_id == -4)
		ft_putstr("Error\ncolor format: r, g, b. Range 0-255.\n");
	else if (error_id == -5)
		ft_putstr("Error\nmissconfig\n");
	else if (error_id == -6)
		ft_putstr("Error\nmalloc ou problema no path das texturas\n");
	else if (error_id == -7)
		ft_putstr("Error\nmap misconfig\n");
	else if (error_id == -8)
		ft_putstr("Error\nunable to conect with graphical system\n");
	else if (error_id == -9)
		ft_putstr("Error\nunable to create a window\n");
	else if (error_id == -10)
		ft_putstr("Error\ncolors values must be in the range 0 - 255\n");
	exit(error_id);
}
