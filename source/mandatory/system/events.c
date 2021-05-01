/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:19:30 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/01 01:41:27 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/cub.h"

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
	return (0);
}
