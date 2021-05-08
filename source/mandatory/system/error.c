/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 00:46:13 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/08 20:28:54 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/cub.h"

static void	print_args_and_mlx_message(int error_id)
{
	if (error_id == -101)
		ft_putendl("Error\nUsage: cub3d file.cub (--save)");
	if (error_id == -102)
	{
		ft_putendl("Error\nThe settings scene must have .cub extension");
		ft_putendl("Usage: cub3d file.cub (--save)");
	}
	if (error_id == -103)
	{
		ft_putendl("Error\nTo save a .bmp image, use the flag --save");
		ft_putendl("Usage: cub3d file.cub (--save)");
	}
	else if (error_id == -104)
		ft_putendl("Error\nNot a valid .cub file");
	else if (error_id == -105)
		ft_putendl("Error\nunable to conect with graphical system");
}

static void	print_map_and_bmp_message(int error_id)
{
	if (error_id == -106)
	{
		ft_putendl("Error\nYour map must have only those characters:");
		ft_putendl("'0' for empty space\n'1' for a wall\n'2' for an item");
		ft_putendl("'N'/'S'/'E'/'W' for player position and orientation");
		ft_putendl("' ' for optional padding");
	}
	else if (error_id == -107)
		ft_putendl("Error\nYour map must be surrounded by walls ('1')");
	else if (error_id == -108)
	{
		ft_putendl("Error\nmap misconfig");
		ft_putendl("You must include a player in your map");
	}
	else if (error_id == -110)
		ft_putendl("Error\ncolors values must be between 0 and 255");
	else if (error_id == -111)
		ft_putendl("Error\nunable to create bmp file");
}

static void	print_texture_message(int error_id)
{
	if (error_id == -112)
		ft_putendl("Error\ninvalid wall texture path");
	else if (error_id == -113)
		ft_putendl("Error\nunable to get wall texture image data");
	else if (error_id == -114)
		ft_putendl("Error\ninvalid sprite texture path");
	else if (error_id == -115)
		ft_putendl("Error\nunable to get sprite texture image data");
	else if (error_id == -116)
	{
		ft_putendl("Error\nsettings missconfig");
		ft_putendl(".cub file must contain:\nR resolution");
		ft_putendl("NO/SO/WE/EA path to the north/south/west/east texture");
		ft_putendl("S path to the sprite texture");
		ft_putendl("F floor colors\nC ceiling colors");
		ft_putendl("a map, composed by those possible characters:");
		ft_putendl("'0' for empty space\n'1' for a wall\n'2' for an item");
		ft_putendl("'N'/'S'/'E'/'W' for player position and orientation");
		ft_putendl("' ' for optional padding");
		ft_putendl("The map must be the last content");
	}
}

static void	print_settings_and_window_message(int error_id)
{
	if (error_id == -117)
		ft_putendl("Error\nResolution settings misconfig");
	else if (error_id == -118)
		ft_putendl("Error\nColors' settings misconfig");
	else if (error_id == -119)
		ft_putendl("Error\nTextures' paths misconfig");
	else if (error_id == -120)
		ft_putendl("Error\nunable to create a window");
}

void	return_error(t_cub *cub, int error_id)
{
	ft_putendl("\x1B[31m---------------------------------------------");
	if (error_id <= -101 && error_id >= -105)
		print_args_and_mlx_message(error_id);
	else if (error_id <= -106 && error_id >= -111)
		print_map_and_bmp_message(error_id);
	else if (error_id <= -112 && error_id >= -116)
		print_texture_message(error_id);
	else if (error_id <= -117 && error_id >= -120)
		print_settings_and_window_message(error_id);
	ft_putendl("\x1B[31m---------------------------------------------\033[0m");
	free_cub(cub);
	exit(error_id);
}
