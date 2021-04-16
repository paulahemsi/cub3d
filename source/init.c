/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 02:32:29 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/16 02:05:34 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_cub(t_cub *cub)
{
	ft_memset(cub, 0, sizeof(*cub));
	ft_memset(&cub->settings.floor, -1, sizeof(cub->settings.floor));
	ft_memset(&cub->settings.ceiling, -1, sizeof(cub->settings.ceiling));
	ft_memset(&cub->toggle, -1, sizeof(cub->toggle));
	cub->toggle.bmp_id = 0;//!rever
	cub->mlx_ptr = mlx_init();
	if (!(cub->mlx_ptr))
		return_error(-8);
}