/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/21 13:14:48 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/10/21 14:22:51 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libraries/MLX42/include/MLX42/MLX42.h"
# include "../libraries/libft/libft.h"
# include <stdio.h>

typedef struct s_player
{
	int	x;
	int	y;
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		col;
	int		row;
}	t_map;

typedef struct s_cub3d
{
	mlx_t		*mlx;
	t_map		map;
	t_player	player;
}	t_cub3d;

// Map parser
void	parse_map(t_cub3d *cub3d);

#endif