/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:19:30 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/05 13:46:40 by phemsi-a         ###   ########.fr       */
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
		img->cub->player.pos[Y]--;
	else if (key == A)
		img->cub->player.pos[X]--;
	else if (key == S)
		img->cub->player.pos[Y]++;
	else if (key == D)
		img->cub->player.pos[X]++;
	else if (key == UP)
	{
		img->cub->player.pos[X] += img->cub->player.delta_x;
		img->cub->player.pos[Y] += img->cub->player.delta_y;
	}
	else if (key == DOWN)
	{
		img->cub->player.pos[X] -= img->cub->player.delta_x;
		img->cub->player.pos[Y] -= img->cub->player.delta_y;
	}
	else if (key == LEFT)
	{
		img->cub->player.angle -= 0.05 * img->cub->player.speed;
		if (img->cub->player.angle < 0)
			img->cub->player.angle += 2 * PI;
		img->cub->player.delta_x = cos(img->cub->player.angle) * 5;
		img->cub->player.delta_y = sin(img->cub->player.angle) * 5;
	}
	else if (key == RIGHT)
	{
		img->cub->player.angle += 0.05 * img->cub->player.speed;
		if (img->cub->player.angle > 2 * PI)
			img->cub->player.angle -= 2 * PI;
		img->cub->player.delta_x = cos(img->cub->player.angle) * 5;
		img->cub->player.delta_y = sin(img->cub->player.angle) * 5;
	}
	else if (key == SHIFT)
		ft_putendl("SHIFT");
	else if (key == SPACE)
		ft_putendl("SPACE");
	else if (key == TAB)
		ft_putendl("TAB");
	return (0);
}

int			key_released(int key, t_data *img)
{
	// if (key == ESC)
	// 	close_cub(img);
	// else if (key == W)
	// 	img->cub->player.pos[Y]--;
	// else if (key == A)
	// 	img->cub->player.pos[X]--;
	// else if (key == S)
	// 	img->cub->player.pos[Y]++;
	// else if (key == D)
	// 	img->cub->player.pos[X]++;
	if (key == UP)
		img->cub->player.move_dir = 0;
	else if (key == DOWN)
		img->cub->player.move_dir = 0;
	else if (key == LEFT)
		img->cub->player.turn_dir = 0;
	else if (key == RIGHT)
		img->cub->player.turn_dir = 0;
	else if (key == SHIFT)
		ft_putendl("SHIFT");
	else if (key == SPACE)
		ft_putendl("SPACE");
	else if (key == TAB)
		ft_putendl("TAB");
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
