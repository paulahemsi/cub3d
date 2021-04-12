/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 02:32:29 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/12 00:25:57 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_cub(t_configs *cub)
{
	ft_memset(cub, 0, sizeof(*cub));
	ft_memset(&cub->floor, -1, sizeof(cub->floor));
	ft_memset(&cub->ceiling, -1, sizeof(cub->ceiling));
	cub->map.show_minimap = -1;
	cub->gradient = -1;
	cub->debug = -1;
}