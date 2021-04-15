/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 02:22:45 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/15 23:27:36 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	free_map(char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static void	free_paths(t_cub *cub)
{
	int	texture;

	texture = NORTH;
	while (texture <= SPRITE)
		free(cub->settings.path[texture]);
}

void		free_cub(t_cub *cub)
{
	free_paths(cub);
	free_map(cub->game.map.row);
}

void		free_all(t_cub *cub)
{
	mlx_destroy_image(cub->mlx_ptr, cub->img->ptr);
	mlx_loop_end(cub->mlx_ptr);
	mlx_destroy_window(cub->mlx_ptr, cub->window_ptr);
	cub->window_ptr = NULL;
	free_cub(cub);
}
