/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 00:46:13 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/30 12:43:34 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	return_error(t_cub *cub, int error_id)
{
	if (error_id == -101)
		ft_putstr("Error\nUsage: cub3d file.cub (--save)\n");
	if (error_id == -102)
		ft_putstr("Error\nThe settings scene must have .cub extension\nUsage: cub3d file.cub (--save)\n");
	if (error_id == -103)
		ft_putstr("Error\nTo save a .bmp image, use the flag --save\nUsage: cub3d file.cub (--save)\n");
	else if (error_id == -104)
		ft_putstr("Error\nNot a valid .cub file\n");
	else if (error_id == -105)
		ft_putstr("Error\nunable to conect with graphical system\n");
	else if (error_id == -106)
		ft_putstr("Error\nmap misconfig\nYour map must have only those characters:\n'0' for empty space\n'1' for a wall\n'2' for an item\n'N'/'S'/'E'/'W' for player start position and spawning orientation\n' ' for optional padding\n");
	else if (error_id == -107)
		ft_putstr("Error\nmap misconfig\nYour map must be surrounded by walls (1)\n");
	else if (error_id == -108)
		ft_putstr("Error\nmap misconfig\nYou must include a player in your map (E, A, S or N, accordingly to spawning orientation)\n");
	else if (error_id == -110)
		ft_putstr("Error\nfloor and ceiling colors values must be between 0 and 255\n");
	else if (error_id == -111)
		ft_putstr("Error\nunable to create bmp file\n");
	else if (error_id == -112)
		ft_putstr("Error\ninvalid wall texture path\n");
	else if (error_id == -113)
		ft_putstr("Error\nunable to get wall texture image data\n");
	else if (error_id == -114)
		ft_putstr("Error\ninvalid sprite texture path\n");
	else if (error_id == -115)
		ft_putstr("Error\nunable to get sprite texture image data\n");
	else if (error_id == -116)
		ft_putstr("Error\nsettings missconfig\n.cub file must contain those type identifiers followed by the specific informations:\nR resolution\nNO path to the north texture\n SO path to the south texture\nWE path to the west texture\nEA path to the east texture\nS path to the sprite texture\nF floor colors\nC ceiling colors\na map, composed by those possible characters:\n'0' for empty space\n'1' for a wall\n'2' for an item\n'N'/'S'/'E'/'W' for player start position and spawning orientation\n' ' for optional padding\nThe map must be the last content");
	else if (error_id == -117)
		ft_putstr("Error\nResolution settings misconfig\n");
	else if (error_id == -118)
		ft_putstr("Error\nColors' settings misconfig\n");
	else if (error_id == -119)
		ft_putstr("Error\nTextures' paths misconfig\n");
	else if (error_id == -120)
		ft_putstr("Error\nunable to create a window\n");
	free_cub(cub);
	exit(error_id);
}
