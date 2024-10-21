/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/21 13:14:48 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/10/21 19:53:49 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libraries/MLX42/include/MLX42/MLX42.h"
# include "../libraries/libft/libft.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>

typedef struct s_player
{
	int		x;
	int		y;
	char	f;
}	t_player;

typedef struct s_map
{
	char			**grid;
	int				info;
	int				col;
	int				row;
	int				f_r;
	int				f_g;
	int				f_b;
	int				c_r;
	int				c_g;
	int				c_b;
	mlx_texture_t	*NO;
	mlx_texture_t	*SO;
	mlx_texture_t	*WE;
	mlx_texture_t	*EA;
}	t_map;

typedef struct s_cub3d
{
	mlx_t		*mlx;
	int			map_fd;
	t_map		map;
	t_player	player;
}	t_cub3d;

// Map parser
void	parse_map(t_cub3d *cub3d);

// Close program
void	close_program(t_cub3d *cub3d, char *msg, int exit_code);
void	error_handler(int i);

// Utils
int		check_whitespace(char c);
int		ft_special_atoi(char *num);

#endif