/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:19:30 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/06 02:24:42 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		close_cub(int key, t_data *img)
{
	mlx_destroy_image(img->mlx_ptr, img->ptr);
	mlx_loop_end(img->mlx_ptr);
	mlx_destroy_window(img->mlx_ptr, img->window_ptr);
	img->window_ptr = NULL;
	exit(0);
	return (0);
}

int			key_pressed(int key, t_data *img)
{
	if (key == ESC)
		close_cub(key, img);
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
	{
		if (img->cub->map.show_minimap)
			img->cub->map.show_minimap = FALSE;
		else
			img->cub->map.show_minimap = TRUE;
	}
	return (0);
}

int			key_released(int key, t_data *img)
{
	if (key == W)
		ft_putendl("REL W");
	else if (key == A)
		ft_putendl("REL A");
	else if (key == S)
		ft_putendl("REL S");
	else if (key == D)
		ft_putendl("REL D");
	if (key == UP)
		ft_putendl("REL UP");
	else if (key == DOWN)
		ft_putendl("REL DOWN");
	else if (key == LEFT)
		ft_putendl("REL LEFT");
	else if (key == RIGHT)
		ft_putendl("REL RIGHT");
	else if (key == SHIFT)
		ft_putendl("REL SHIFT");
	else if (key == SPACE)
		ft_putendl("REL SPACE");
	return (0);
}

int			mouse_clicked(int button, int pos_x, int pos_y, t_data *img)
{
	if ((button == MOUSE_1) || (button == MOUSE_2) || (button == MOUSE_3))
	{
		mlx_mouse_get_pos(img->mlx_ptr, img->window_ptr, &pos_x, &pos_y);
		ft_printf("Button pressed: %i\n(%4d, %4d)\n", button, pos_x, pos_y);
	}
	return (0);
}
