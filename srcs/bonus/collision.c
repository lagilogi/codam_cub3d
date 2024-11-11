/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collision.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/08 16:29:59 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/11/08 16:30:40 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	check_forward(t_cub3d *cub3d, float dis_y, float dis_x, float angle)
{
	dis_y = cub3d->player.y - sin(angle) * 0.25;
	dis_x = cub3d->player.x - cos(angle) * 0.25;
	printf("forward Y: %.2f x: %.2f angle: %.2f    ", dis_y, dis_x, angle);
	// printf("forward Y: %d x: %d     ", (int)dis_y, (int)dis_x);
	if (cub3d->map.grid[(int)dis_y][(int)dis_x] == '1')
		return (true);

	angle = cub3d->player.angle - 0.25 * PI;
	if (angle < 0)
		angle = cub3d->player.angle + 1.75 * PI;
	dis_y = cub3d->player.y - sin(angle) * 0.25;
	dis_x = cub3d->player.x - cos(angle) * 0.25;
	printf("left Y: %.2f x: %.2f angle: %.2f   ", dis_y, dis_x, angle);
	// printf("left Y: %d x: %d     ", (int)dis_y, (int)dis_x);
	if (cub3d->map.grid[(int)dis_y][(int)dis_x] == '1')
		return (true);

	angle = cub3d->player.angle + 0.25 * PI;
	if (angle > 2 * PI)
		angle = cub3d->player.angle - 1.75 * PI;
	dis_y = cub3d->player.y - sin(angle) * 0.25;
	dis_x = cub3d->player.x - cos(angle) * 0.25;
	printf("right Y: %.2f x: %.2f angle: %.2f     -  ", dis_y, dis_x, angle);
	// printf("right Y: %d x: %d     -  ", (int)dis_y, (int)dis_x);
	if (cub3d->map.grid[(int)dis_y][(int)dis_x] == '1')
		return (true);
	return (false);
}

static bool	check_backward(t_cub3d *cub3d, float dis_y, float dis_x, float angle)
{
	angle = cub3d->player.angle - PI;
	if (angle < 0)
		angle = cub3d->player.angle + PI;
	dis_y = cub3d->player.y - sin(angle) * 0.25;
	dis_x = cub3d->player.x - cos(angle) * 0.25;
	printf("Backward Y: %.2f x: %.2f angle: %.2f    ", dis_y, dis_x, angle);
	if (cub3d->map.grid[(int)dis_y][(int)dis_x] == '1')
		return (true);
	angle = cub3d->player.angle - 0.75 * PI;
	if (angle < 0)
		angle = cub3d->player.angle + 1.25 * PI;
	dis_y = cub3d->player.y - sin(angle) * 0.25;
	dis_x = cub3d->player.x - cos(angle) * 0.25;
	printf("Left Y: %.2f x: %.2f angle: %.2f    ", dis_y, dis_x, angle);
	if (cub3d->map.grid[(int)dis_y][(int)dis_x] == '1')
		return (true);
	angle = cub3d->player.angle + 0.75 * PI;
	if (angle > 2 * PI)
		angle = cub3d->player.angle - 1.25 * PI;
	dis_y = cub3d->player.y - sin(angle) * 0.25;
	dis_x = cub3d->player.x - cos(angle) * 0.25;
	printf("Right Y: %.2f x: %.2f angle: %.2f    ", dis_y, dis_x, angle);
	if (cub3d->map.grid[(int)dis_y][(int)dis_x] == '1')
		return (true);
	return (false);
}

static bool	check_left(t_cub3d *cub3d, float dis_y, float dis_x)
{
	float	angle;

	angle = cub3d->player.angle - 1.5 * PI;
	if (angle < 0)
		angle = cub3d->player.angle + 0.5 * PI;
	dis_y = cub3d->player.y - sin(angle) * 0.25;
	dis_x = cub3d->player.x - cos(angle) * 0.25;
	printf("Left Y: %.2f x: %.2f angle: %.2f    ", dis_y, dis_x, angle);
	if (cub3d->map.grid[(int)dis_y][(int)dis_x] == '1')
		return (true);
	angle = cub3d->player.angle - 1.25 * PI;
	if (angle < 0)
		angle = cub3d->player.angle + 0.75 * PI;
	dis_y = cub3d->player.y - sin(angle) * 0.25;
	dis_x = cub3d->player.x - cos(angle) * 0.25;
	printf("up Y: %.2f x: %.2f angle: %.2f    ", dis_y, dis_x, angle);
	if (cub3d->map.grid[(int)dis_y][(int)dis_x] == '1')
		return (true);
	angle = cub3d->player.angle - 1.75 * PI;
	if (angle < 0)
		angle = cub3d->player.angle + 0.25 * PI;
	dis_y = cub3d->player.y - sin(angle) * 0.25;
	dis_x = cub3d->player.x - cos(angle) * 0.25;
	printf("down Y: %.2f x: %.2f angle: %.2f    ", dis_y, dis_x, angle);
	if (cub3d->map.grid[(int)dis_y][(int)dis_x] == '1')
		return (true);
	return (false);
}

static bool	check_right(t_cub3d *cub3d, float dis_y, float dis_x)
{
	float	angle;
	angle = cub3d->player.angle - 0.5 * PI;
	if (angle < 0)
		angle = cub3d->player.angle + 1.5 * PI;
	dis_y = cub3d->player.y - sin(angle) * 0.25;
	dis_x = cub3d->player.x - cos(angle) * 0.25;
	if (cub3d->map.grid[(int)dis_y][(int)dis_x] == '1')
		return (true);
	angle = cub3d->player.angle - 0.25 * PI;
	if (angle < 0)
		angle = cub3d->player.angle + 1.75 * PI;
	dis_y = cub3d->player.y - sin(angle) * 0.25;
	dis_x = cub3d->player.x - cos(angle) * 0.25;
	if (cub3d->map.grid[(int)dis_y][(int)dis_x] == '1')
		return (true);
	angle = cub3d->player.angle - 0.75 * PI;
	if (angle < 0)
		angle = cub3d->player.angle + 1.25 * PI;
	dis_y = cub3d->player.y - sin(angle) * 0.25;
	dis_x = cub3d->player.x - cos(angle) * 0.25;
	if (cub3d->map.grid[(int)dis_y][(int)dis_x] == '1')
		return (true);
	return (false);
}

bool	collision_check(t_cub3d *cub3d, char c)
{
	if (c == 'W' && check_forward(cub3d, 0, 0, cub3d->player.angle))
		return (true);
	else if (c == 'S' && check_backward(cub3d, 0, 0, cub3d->player.angle))
		return (true);
	else if (c == 'A' && check_left(cub3d, 0, 0))
		return (true);
	else if (c == 'D' && check_right(cub3d, 0, 0))
		return (true);
	return (false);
}
