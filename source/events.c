/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:19:30 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/03/27 01:11:45 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int key_is_pressed(int key, t_data *img)
{
	if (key == ESC)
	{
		mlx_loop_end(img->mlx_ptr);
		//mlx_destroy_image(img->mlx_ptr, img->ptr);
		mlx_destroy_window(img->mlx_ptr, img->window_ptr);
	}
	else if (key == W)
		ft_putendl("W");
	else if (key == A)
		ft_putendl("A");
	else if (key == S)
		ft_putendl("S");
	else if (key == D)
		ft_putendl("D");
	else if (key == UP)
		ft_putendl("UP");
	else if (key == DOWN)
		ft_putendl("DOWN");
	else if (key == LEFT)
		ft_putendl("LEFT");
	else if (key == RIGHT)
		ft_putendl("RIGHT");
	else if (key == SHIFT)
		ft_putendl("SHIFT");
	else if (key == SPACE)
		ft_putendl("SPACE");
	else if (key == TAB)
		ft_putendl("TAB");
	else
		ft_putendl("ordinary key pressed");
	return (0);
}

int		mouse_clicked(int button, int pos_x, int pos_y, t_data *img)
{
	if ((button == MOUSE_1) || (button == MOUSE_2) || (button == MOUSE_3))
	{
		mlx_mouse_get_pos(img->mlx_ptr, img->window_ptr, &pos_x, &pos_y);
		ft_printf("Button pressed: %i\n(%4d, %4d)\n", button, pos_x, pos_y);
	}
	return (0);
}