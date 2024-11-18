/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collision.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/08 16:29:59 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/11/15 18:34:32 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	check_forward(t_cub3d *cub3d, float dis_y, float dis_x, float angle)
{
	dis_y = cub3d->player.y - sin(cub3d->player.angle) * COL;
	dis_x = cub3d->player.x - cos(cub3d->player.angle) * COL;
	if (out_of_bounds(cub3d, (int)dis_y, (int)dis_x)
		|| check_coll_char(cub3d->map.grid[(int)dis_y][(int)dis_x]))
		return (true);
	angle = cub3d->player.angle - 0.25 * PI;
	if (angle < 0)
		angle += PI * 2;
	dis_y = cub3d->player.y - sin(angle) * COL;
	dis_x = cub3d->player.x - cos(angle) * COL;
	if (check_coll_char(cub3d->map.grid[(int)dis_y][(int)dis_x]))
		return (true);
	angle = cub3d->player.angle + 0.25 * PI;
	if (angle > 2 * PI)
		angle -= PI * 2;
	dis_y = cub3d->player.y - sin(angle) * COL;
	dis_x = cub3d->player.x - cos(angle) * COL;
	if (check_coll_char(cub3d->map.grid[(int)dis_y][(int)dis_x]))
		return (true);
	return (false);
}

static bool	check_back(t_cub3d *cub3d, float dis_y, float dis_x, float angle)
{
	angle = cub3d->player.angle - PI;
	if (angle < 0)
		angle += PI * 2;
	dis_y = cub3d->player.y - sin(angle) * COL;
	dis_x = cub3d->player.x - cos(angle) * COL;
	if (out_of_bounds(cub3d, (int)dis_y, (int)dis_x)
		|| check_coll_char(cub3d->map.grid[(int)dis_y][(int)dis_x]))
		return (true);
	angle = cub3d->player.angle - 0.75 * PI;
	if (angle < 0)
		angle += PI * 2;
	dis_y = cub3d->player.y - sin(angle) * COL;
	dis_x = cub3d->player.x - cos(angle) * COL;
	if (check_coll_char(cub3d->map.grid[(int)dis_y][(int)dis_x]))
		return (true);
	angle = cub3d->player.angle + 0.75 * PI;
	if (angle > 2 * PI)
		angle -= PI * 2;
	dis_y = cub3d->player.y - sin(angle) * COL;
	dis_x = cub3d->player.x - cos(angle) * COL;
	if (check_coll_char(cub3d->map.grid[(int)dis_y][(int)dis_x]))
		return (true);
	return (false);
}

static bool	check_right(t_cub3d *cub3d, float dis_y, float dis_x, float angle)
{
	angle = cub3d->player.angle - 1.5 * PI;
	if (angle < 0)
		angle += PI * 2;
	dis_y = cub3d->player.y - sin(angle) * COL;
	dis_x = cub3d->player.x - cos(angle) * COL;
	if (out_of_bounds(cub3d, (int)dis_y, (int)dis_x)
		|| check_coll_char(cub3d->map.grid[(int)dis_y][(int)dis_x]))
		return (true);
	angle = cub3d->player.angle - 1.25 * PI;
	if (angle < 0)
		angle += PI * 2;
	dis_y = cub3d->player.y - sin(angle) * COL;
	dis_x = cub3d->player.x - cos(angle) * COL;
	if (check_coll_char(cub3d->map.grid[(int)dis_y][(int)dis_x]))
		return (true);
	angle = cub3d->player.angle - 1.75 * PI;
	if (angle < 0)
		angle += PI * 2;
	dis_y = cub3d->player.y - sin(angle) * COL;
	dis_x = cub3d->player.x - cos(angle) * COL;
	if (check_coll_char(cub3d->map.grid[(int)dis_y][(int)dis_x]))
		return (true);
	return (false);
}

static bool	check_left(t_cub3d *cub3d, float dis_y, float dis_x, float angle)
{
	angle = cub3d->player.angle - 0.5 * PI;
	if (angle < 0)
		angle += PI * 2;
	dis_y = cub3d->player.y - sin(angle) * COL;
	dis_x = cub3d->player.x - cos(angle) * COL;
	if (out_of_bounds(cub3d, (int)dis_y, (int)dis_x)
		|| check_coll_char(cub3d->map.grid[(int)dis_y][(int)dis_x]))
		return (true);
	angle = cub3d->player.angle - 0.25 * PI;
	if (angle < 0)
		angle += PI * 2;
	dis_y = cub3d->player.y - sin(angle) * COL;
	dis_x = cub3d->player.x - cos(angle) * COL;
	if (check_coll_char(cub3d->map.grid[(int)dis_y][(int)dis_x]))
		return (true);
	angle = cub3d->player.angle - 0.75 * PI;
	if (angle < 0)
		angle += PI * 2;
	dis_y = cub3d->player.y - sin(angle) * COL;
	dis_x = cub3d->player.x - cos(angle) * COL;
	if (check_coll_char(cub3d->map.grid[(int)dis_y][(int)dis_x]))
		return (true);
	return (false);
}

bool	collision_check(t_cub3d *cub3d, char c)
{
	if (c == 'W' && check_forward(cub3d, 0, 0, 0))
		return (true);
	else if (c == 'S' && check_back(cub3d, 0, 0, 0))
		return (true);
	else if (c == 'A' && check_left(cub3d, 0, 0, 0))
		return (true);
	else if (c == 'D' && check_right(cub3d, 0, 0, 0))
		return (true);
	cub3d->moving = true;
	return (false);
}
