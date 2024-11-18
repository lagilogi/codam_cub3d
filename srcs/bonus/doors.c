#include "../../include/cub3d.h"

int	door_validity(t_cub3d *cub3d, int y, int x)
{
	if (cub3d->map.grid[y + 1][x] == '1' && cub3d->map.grid[y - 1][x] == '1')
		if (cub3d->map.grid[y][x + 1] == '0' && cub3d->map.grid[y][x - 1] == '0')
			return (true);
	if (cub3d->map.grid[y][x + 1] == '1' && cub3d->map.grid[y][x - 1] == '1')
		if (cub3d->map.grid[y + 1][x] == '0' && cub3d->map.grid[y - 1][x] == '0')
			return (true);
	return (false);
}

void	open_close_door(t_cub3d *cub3d, float y, float x)
{
	float	delta_y;
	float	delta_x;
	int		i;

	i = 0;
	delta_y = sin(cub3d->player.angle);
	delta_x = cos(cub3d->player.angle);
	while (i < 40)
	{
		y -= delta_y * 0.025;
		x -= delta_x * 0.025;
		if (cub3d->map.grid[(int)y][(int)x] == 'D' || cub3d->map.grid[(int)y][(int)x] == 'd')
		{
			cub3d->moving = true;
			if (cub3d->map.grid[(int)y][(int)x] == 'D')
				cub3d->map.grid[(int)y][(int)x] = 'd';
			else if (cub3d->map.grid[(int)y][(int)x] == 'd')
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
