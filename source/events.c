/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:19:30 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/07 00:12:03 by phemsi-a         ###   ########.fr       */
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

static void	update_turn_direction(int direction, t_player *player)
{
	player->turn_dir += direction;
	player->angle += player->turn_dir * (player->speed * PI / 180);
	player->angle = remainder(player->angle, TWO_PI);
	if (player->angle < 0)
		player->angle += TWO_PI;
}

static int	is_tile_free(float *pos, t_configs *cub)
{
	int minimap[2];

	if (pos[X] < 0 || pos[X] > cub->world_width || pos[Y] < 0 || pos[Y] > cub->world_height)
		return (FALSE);
	minimap[X] = floor(pos[X] / TILE_SIZE);
	minimap[Y] = floor(pos[Y] / TILE_SIZE);
	ft_printf("minimap (%i, %i) content %c", minimap[X], minimap[Y], cub->map.row[minimap[X]][minimap[Y]]);
	if (minimap[X] >= cub->map.total_column || minimap[Y] >= cub->map.total_row)
		return (FALSE);
	if (cub->map.row[minimap[X]][minimap[Y]] == '0')
		return (TRUE);
	return (FALSE);
}

static void	update_move_direction(int direction, t_player *player, t_configs *cub)
{
	float step;
	float new_position[2];

	player->move_dir += direction;
	step = player->move_dir * player->speed;
	new_position[X] = player->pos[X] + (cos(player->angle) * step);
	new_position[Y] = player->pos[Y] + (sin(player->angle) * step);
	//is_tile_free(new_position, cub);
	//{
		printf("player pos (%i, %i)\n", player->pos[X], player->pos[Y]);
		player->pos[X] = new_position[X];
		player->pos[Y] = new_position[Y];
	//}
}

int			key_pressed(int key, t_data *img)
{
	if (key == ESC)
		close_cub(key, img);
	if (key == W)
		update_move_direction(1, &img->cub->player, img->cub);
	else if (key == A)
		ft_putendl("A");
	else if (key == S)
		update_move_direction(-1, &img->cub->player, img->cub);
	else if (key == D)
		ft_putendl("D");
	if (key == UP)
		update_move_direction(1, &img->cub->player, img->cub);
	else if (key == DOWN)
		update_move_direction(-1, &img->cub->player, img->cub);
	if (key == LEFT)
		update_turn_direction(-1, &img->cub->player);
	else if (key == RIGHT)
		update_turn_direction(1, &img->cub->player);
	else if (key == SHIFT)
		ft_putendl("SHIFT");
	else if (key == SPACE)
		ft_putendl("SPACE");
	else if (key == TAB)
		img->cub->map.show_minimap *= TOGGLE;
	return (0);
}

int			key_released(int key, t_data *img)
{
	if (key == W)
		img->cub->player.move_dir = 0;
	else if (key == A)
		ft_putendl("REL A");
	else if (key == S)
		img->cub->player.move_dir = 0;
	else if (key == D)
		ft_putendl("REL D");
	else if (key == UP)
		img->cub->player.move_dir = 0;
	else if (key == DOWN)
		img->cub->player.move_dir = 0;
	else if (key == LEFT)
		img->cub->player.turn_dir = 0;
	else if (key == RIGHT)
		img->cub->player.turn_dir = 0;
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
