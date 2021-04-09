/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 22:21:41 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/05 17:54:08 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static int	is_ray_facing_down(float	angle)
{
	if (angle > 0 && angle < PI)
		return (TRUE);
	else
		return (FALSE);
}

static int	is_ray_facing_right(float	angle)
{
	if (angle < PI / 2 || angle > 1.5 * PI)
		return (TRUE);
	else
		return (FALSE);
}


static void	find_horizontal_collision(t_configs *cub)
{
	int		intersection[2];
	int		grid[2];
	int		increment[2];

	cub->ray.angle = floor(cub->player.angle - (FOV / 2.0));
	if (cub->ray.angle < 0)
		cub->ray.angle = floor((360 * (PI / 180)) + cub->ray.angle);
	if (is_ray_facing_down(cub->ray.angle))
	{
		intersection[Y] = floor(cub->player.pos[Y] / 64) * 64 + 64;
		increment[Y] = TILE_SIZE;
	}
	else
	{
		intersection[Y] = floor(cub->player.pos[Y] / 64) * 64 - 1;
		increment[Y] = -TILE_SIZE;
	}
	intersection[X] = cub->player.pos[X] + (cub->player.pos[Y] - intersection[Y]) / tan(cub->ray.angle); //TODO tabela de tangentes para evitar contas
	grid[X] = floor(intersection[X] / TILE_SIZE);
	grid[Y] = floor(intersection[Y] / TILE_SIZE);
	increment[X] = 64 / tan(cub->ray.angle);
	while (cub->map.row[grid[X]][grid[Y]] == '0')
	{
		intersection[X] += increment[X];
		intersection[Y] += increment[Y];
		grid[X] = floor(intersection[X] / TILE_SIZE);
		grid[Y] = floor(intersection[Y] / TILE_SIZE);
	}
	cub->ray.hor_col[X] = grid[X];
	cub->ray.hor_col[Y] = grid[Y];
}

void	put_walls(t_data *img)
{
	float	angle;
	int 	i;

	angle = img->cub->player.angle - (FOV / 2);
	i = 0;
	while (i < 1)
	{
		find_horizontal_collision(img->cub);
		i++;
	}
}
