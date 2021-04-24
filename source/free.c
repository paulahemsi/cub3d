/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 02:22:45 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/24 13:45:43 by phemsi-a         ###   ########.fr       */
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

void	free_paths(char **path)
{
	int	texture;

	texture = NORTH;
	while (texture <= SPRITE)
	{
		if (path[texture])
		{
			free(path[texture]);
			path[texture] = NULL;
		}
		texture++;
	}
}

void	free_cub(t_cub *cub)
{
	free_paths(cub->settings.path); //!dar free antes daqui, assim que carregar imgs das texturas
	free_map(cub->game.map.row);
}

void		free_all(t_cub *cub)
{
	free_cub(cub);
	if (cub->img.ptr && cub->mlx_ptr)
		mlx_destroy_image(cub->mlx_ptr, cub->img.ptr);
	if (cub->window_ptr && cub->mlx_ptr)
		mlx_destroy_window(cub->mlx_ptr, cub->window_ptr);
	//mlx_loop_end(cub->mlx_ptr);
	//free(cub->mlx_ptr);
	//cub->window_ptr = NULL;
}

//!destruir janela destruir display free mlx
