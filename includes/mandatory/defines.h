/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:26:25 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/01 02:46:47 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/*
** game
*/
# define TILE_SIZE		64
# define HALF_TILE		32
# define PLAYER_HEIGHT	32
# define SCALE			0.12
# define TOGGLE			-1
/*
** maths
*/
# define PI				3.14159265
# define TWO_PI			6.28316530
# define FOV			1.047198
# define HALF_FOV		0.523599
/*
** events
*/
# define ESC			0xff1b
# define LEFT			0xff51
# define UP				0xff52
# define RIGHT			0xff53
# define DOWN			0xff54
# define W				0x0077
# define A				0x0061
# define S				0x0073
# define D				0x0064
# define Q				0x0071
# define E				0x0065
/*
** aux
*/
# define X				0
# define Y				1
# define ROW			1
# define COL			0
# define HOR			0
# define VER			1
# define NORTH			0
# define SOUTH			1
# define EAST			2
# define WEST			3
# define SPRITE			4
# define CEILING		0
# define FLOOR			1
# define FRONT			0
# define MOVE			0
# define SIDE			1
# define TURN			2
# define WIDTH			0
# define HEIGHT			1
# define TOP			0
# define BOTTOM			1
# define VALID_CELL		1
# define EDGE			0

#endif
