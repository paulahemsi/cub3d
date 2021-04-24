/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:26:25 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/24 01:42:37 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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


# define TILE_SIZE		64
# define HALF_TILE		32
# define PLAYER_HEIGHT	32
# define SCALE			0.1
# define TOGGLE			-1
/*
** maths
*/
# define PI				3.14159265
# define TWO_PI			6.28316530
# define FOV			60 * (PI / 180)
# define HALF_FOV		FOV / 2
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
# define G				0x0067
# define B				0x0062
# define P				0x0070
# define N				0x006e
# define Q				0x0071
# define E				0x0065
# define SPACE			0x0020
# define TAB			0xff09
# define SHIFT			0xffe1
# define MOUSE_1		1
# define MOUSE_2		2
# define MOUSE_3		3
# define KEYPRESS		2
# define KEYRELEASE		3
# define CLIENTMESSAGE	33
# define KEYPRESS_MASK	1L<<0
# define KEYREL_MASK	1L<<1
# define NOTIFY_MASK	1L<<17