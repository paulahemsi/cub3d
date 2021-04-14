/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:19:30 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/14 04:31:56 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		close_cub(int key, t_data *img)
{
	//free_all(img);
	exit(0);
}

static void	update_player_direction(int key, t_data *img)
{
	if (key == W)
		img->cub->player.move_dir = 1;
	else if (key == S)
		img->cub->player.move_dir = -1;
	if (key == A)
	{
		img->cub->player.move_dir = -1;
		img->cub->player.direction[SIDE] = TRUE;
	}
	else if (key == D)
	{
		img->cub->player.move_dir = 1;
		img->cub->player.direction[SIDE] = TRUE;	
	}
}

static void	update_effects(int key, t_data *img)
{
	if ((key == G) && (img->cub->night_mode == -1))
		img->cub->gradient *= TOGGLE;
	if (key == B)
	{
		img->cub->debug *= TOGGLE;
		img->cub->night_mode = -1;
	}
	if (key == N)
	{
		img->cub->night_mode *= TOGGLE;
		img->cub->debug = -1;
		img->cub->gradient = 1;
	}
}

int		key_pressed(int key, t_data *img)
{
	if (key == ESC)
		close_cub(key, img);
	if (key == W || key == A || key == S || key == D)
		update_player_direction(key, img);
	if (key == LEFT)
		img->cub->player.turn_dir = -1;
	else if (key == RIGHT)
		img->cub->player.turn_dir = 1;
	else if (key == SHIFT)
	{
		img->cub->player.speed = 20;
		img->cub->player.rotate_speed = 6 * PI / 180;
	}
	else if (key == P)
	{
		img->cub->bmp_id ++;
		save_bmp(img);
	}
	if (key == TAB)
		img->cub->map.show_minimap *= TOGGLE;
	if (key == G || key == B || key == N)
		update_effects(key, img);
	return (0);
}

int		key_released(int key, t_data *img)
{
	if (key == W || key == S)
		img->cub->player.move_dir = 0;
	if (key == A || key == D)
	{
		img->cub->player.move_dir = 0;
		img->cub->player.direction[SIDE] = FALSE;
	}
	else if (key == UP)
		img->cub->player.move_dir = 0;
	else if (key == DOWN)
		img->cub->player.move_dir = 0;
	if (key == LEFT)
		img->cub->player.turn_dir = 0;
	else if (key == RIGHT)
		img->cub->player.turn_dir = 0;
	if (key == SHIFT)
	{
		img->cub->player.speed = 7;
		img->cub->player.rotate_speed = 2 * PI / 180;
	}
	// else if (key == SPACE)
		// img->cub->player.invisible = FALSE;
	return (0);
}

// int		mouse_clicked(int button, int pos_x, int pos_y, t_data *img)
// {
// 	if ((button == MOUSE_1) || (button == MOUSE_2) || (button == MOUSE_3))
// 	{
// 		mlx_mouse_get_pos(img->mlx_ptr, img->window_ptr, &pos_x, &pos_y);
// 		ft_printf("Button pressed: %i\n(%4d, %4d)\n", button, pos_x, pos_y);
// 	}
// 	return (0);
// }
