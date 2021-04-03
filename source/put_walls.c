/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 22:21:41 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/02 23:51:46 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static int	is_ray_facing_down(float	angle)
{
	if (angle > 0 && angle < PI)
		return (TRUE);
	else
		return (FALSE);
}

static void	find_horizontal_collision(t_configs *cub)
{
	int		intersection[2];
	int		grid[2];
	int		increment[2];

	cub->ray.angle = cub->player.angle - (FOV / 2.0);
	printf("RAY ANGLE: %f\n", cub->ray.angle);
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
	intersection[X] = cub->player.pos[X] + (cub->player.pos[Y] - intersection[Y]) / tan(cub->ray.angle); //TODO tabela de tangestes para evitar contas
	printf("intersection pxl: (%i, %i)\n", intersection[X], intersection[Y]);
	grid[X] = floor(intersection[X] / TILE_SIZE);
	grid[Y] = floor(intersection[Y] / TILE_SIZE);
	increment[X] = 64 / tan(cub->ray.angle);
	printf("intersection grid: (%i, %i)\n", grid[X], grid[Y]);
	while (cub->map.row[grid[X]][grid[Y]] == '0')
	{
		printf("intersection grid: (%i, %i)\n", grid[X], grid[Y]);
		printf("intersection pxl: (%i, %i)\n", intersection[X], intersection[Y]);
		intersection[X] += increment[X];
		intersection[Y] += increment[Y];
		grid[X] = floor(intersection[X] / TILE_SIZE);
		grid[Y] = floor(intersection[Y] / TILE_SIZE);
	}
	cub->ray.hor_col[X] = grid[X];
	cub->ray.hor_col[Y] = grid[Y];
	printf("ray angle: %f\nhit wall! (%i, %i)\n", cub->ray.angle, cub->ray.hor_col[X], cub->ray.hor_col[Y]);
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

	//printf("ray angle: %f\n player angle: %f\nFOV %f\n", cub->ray.angle * 180 / PI, cub->player.angle * 180 / PI, FOV * 180 / PI);
	//printf("is ray facing down? %i\n", is_ray_facing_down(cub->ray.angle));
	