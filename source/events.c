/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:19:30 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/17 22:49:00 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		close_cub(int key, t_cub *cub)
{
	free_all(cub);
	exit(0);
}

static void	update_player_direction(int key, int *player_direction)
{
	if (key == W)
		player_direction[MOVE] = 1;
	else if (key == S)
		player_direction[MOVE] = -1;
	if (key == A)
	{
		player_direction[MOVE] = -1;
		player_direction[SIDE] = TRUE;
	}
	else if (key == D)
	{
		player_direction[MOVE] = 1;
		player_direction[SIDE] = TRUE;	
	}
}

static void	update_effects(int key, t_toggle *toggle)
{
	if ((key == G) && (toggle->night_mode == -1))
		toggle->gradient *= TOGGLE;
	if (key == B)
	{
		toggle->debug *= TOGGLE;
		toggle->night_mode = -1;
	}
	if (key == N)
	{
		toggle->night_mode *= TOGGLE;
		toggle->debug = -1;
		toggle->gradient = 1;
	}
}

int		key_pressed(int key, t_cub *cub)
{
	if (key == ESC)
		close_cub(key, cub);
	if (key == W || key == A || key == S || key == D)
		update_player_direction(key, cub->game.player.direction);
	if (key == LEFT || key == Q)
		cub->game.player.direction[TURN] = -1;
	else if (key == RIGHT || key == E)
		cub->game.player.direction[TURN] = 1;
	else if (key == SHIFT)
	{
		cub->game.player.speed = 20;
		cub->game.player.rotate_speed = 6 * PI / 180;
	}
	else if (key == P)
	{
		cub->toggle.bmp_id ++;
		save_bmp(cub);
	}
	if (key == TAB)
		cub->toggle.show_minimap *= TOGGLE;
	if (key == G || key == B || key == N)
		update_effects(key, &cub->toggle);
	return (0);
}

int		key_released(int key, t_cub *cub)
{
	if (key == W || key == S)
		cub->game.player.direction[MOVE] = 0;
	if (key == A || key == D)
	{
		cub->game.player.direction[MOVE] = 0;
		cub->game.player.direction[SIDE] = FALSE;
	}
	else if (key == UP)
		cub->game.player.direction[MOVE] = 0;
	else if (key == DOWN)
		cub->game.player.direction[MOVE] = 0;
	if (key == LEFT || key == Q)
		cub->game.player.direction[TURN] = 0;
	else if (key == RIGHT || key == E)
		cub->game.player.direction[TURN] = 0;
	if (key == SHIFT)
	{
		cub->game.player.speed = 7;
		cub->game.player.rotate_speed = 1.5 * PI / 180;
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
