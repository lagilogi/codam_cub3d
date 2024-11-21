/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleunin <saleunin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:00:29 by wsonepou          #+#    #+#             */
/*   Updated: 2024/11/21 13:01:04 by saleunin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	load_doors(t_cub3d *cub3d)
{
	if (cub3d->file.door == false)
		return ;
	cub3d->map.closed_door = mlx_load_png("./textures/closed_door.png");
	if (cub3d->map.closed_door == NULL)
		execution_error_handler(cub3d, 5);
	cub3d->map.open_door = mlx_load_png("./textures/open_door.png");
	if (cub3d->map.open_door == NULL)
		execution_error_handler(cub3d, 5);
}

int	door_validity(t_cub3d *cub3d, int y, int x)
{
	if (y == 0 || x == 0 || y == cub3d->map.rows - 1
		|| x == cub3d->map.cols - 1)
		return (false);
	if (cub3d->map.grid[y + 1][x] == '1' && cub3d->map.grid[y - 1][x] == '1')
		if (cub3d->map.grid[y][x + 1] == '0'
			&& cub3d->map.grid[y][x - 1] == '0')
			return (true);
	if (cub3d->map.grid[y][x + 1] == '1' && cub3d->map.grid[y][x - 1] == '1')
		if (cub3d->map.grid[y + 1][x] == '0'
			&& cub3d->map.grid[y - 1][x] == '0')
			return (true);
	return (false);
}

static void	open_close_door(t_cub3d *cub3d, float y, float x)
{
	float	delta_y;
	float	delta_x;
	int		i;

	i = 0;
	delta_y = sin(cub3d->player.angle) + 0.2;
	delta_x = cos(cub3d->player.angle) + 0.2;
	while (i < 40)
	{
		y -= delta_y * 0.025;
		x -= delta_x * 0.025;
		if (cub3d->map.grid[(int)y][(int)x] == 'D'
			|| cub3d->map.grid[(int)y][(int)x] == 'd')
		{
			cub3d->moving = true;
			if (cub3d->map.grid[(int)y][(int)x] == 'D')
				cub3d->map.grid[(int)y][(int)x] = 'd';
			else if (cub3d->map.grid[(int)y][(int)x] == 'd' && i > 5)
				cub3d->map.grid[(int)y][(int)x] = 'D';
			break ;
		}
		i++;
	}
}

void	check_door(mlx_key_data_t keydata, void *param)
{
	t_cub3d	*cub3d;
	int		y;
	int		x;

	cub3d = param;
	y = cub3d->player.y;
	x = cub3d->player.x;
	if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_SPACE
		&& !(cub3d->map.grid[y][x] == 'D' || cub3d->map.grid[y][x] == 'd'))
		open_close_door(cub3d, cub3d->player.y, cub3d->player.x);
}
