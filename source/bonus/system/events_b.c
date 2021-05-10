/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:19:30 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/10 13:18:41 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub.h"

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

static void	update_effects(int key, t_toggle *toggle, t_item *has)
{
	if (key == B)
	{
		toggle->debug *= TOGGLE;
		toggle->night_mode = -1;
	}
	if ((key == N) && (has->glasses))
	{
		toggle->night_mode *= TOGGLE;
		toggle->debug = -1;
	}
	if ((key == M) && (has->map))
		toggle->show_minimap *= TOGGLE;
}

int	key_pressed(int key, t_cub *cub)
{
	if (key == ESC)
		close_cub(cub);
	if (key == W || key == A || key == S || key == D)
		update_player_direction(key, cub->game.player.direction);
	if (key == LEFT || key == Q)
		cub->game.player.direction[TURN] = -1;
	else if (key == RIGHT || key == E)
		cub->game.player.direction[TURN] = 1;
	else if (key == SHIFT)
	{
		cub->game.player.speed = 20;
		cub->game.player.rotate_speed = 4 * PI / 180;
	}
	else if (key == P)
	{
		cub->toggle.bmp_id ++;
		save_bmp(cub);
	}
	if (key == G || key == B || key == N || key == M)
		update_effects(key, &cub->toggle, &cub->game.item);
	return (0);
}

int	key_released(int key, t_cub *cub)
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
		cub->game.player.speed = 10;
		cub->game.player.rotate_speed = 2.5 * PI / 180;
	}
	return (0);
}

int	mouse_clicked(int button, int pos_x, int pos_y, t_cub *cub)
{
	if ((button == MOUSE_1) || (button == MOUSE_2) || (button == MOUSE_3))
	{
		mlx_mouse_get_pos(cub->mlx_ptr, cub->window_ptr, &pos_x, &pos_y);
		ft_printf("Button pressed: %i\n(%4d, %4d)\n", button, pos_x, pos_y);
	}
	return (0);
}
