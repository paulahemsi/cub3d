/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free..c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 02:22:45 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/11 02:30:14 by phemsi-a         ###   ########.fr       */
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

static void	free_paths(t_configs *cub)
{
	free(cub->path.north);
	free(cub->path.south);
	free(cub->path.west);
	free(cub->path.east);
	free(cub->path.sprite);
}

void		free_cub(t_configs *cub)
{
	free_paths(cub);
	free_map(cub->map.row);
}

void		free_all(t_data *img)
{
	mlx_destroy_image(img->mlx_ptr, img->ptr);
	mlx_loop_end(img->mlx_ptr);
	mlx_destroy_window(img->mlx_ptr, img->window_ptr);
	img->window_ptr = NULL;
	free_cub(img->cub);
}
