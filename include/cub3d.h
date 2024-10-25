/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/21 13:14:48 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/10/24 19:47:31 by wsonepou      ########   odam.nl         */
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
	char	facing;
}	t_player;

typedef struct s_file
{
	int		addit_data_count;
	int		map_cols;
	int		map_rows;
	int		NO;
	int		SO;
	int		WE;
	int		EA;
	int		F;
	int		C;
	int		lines_till_map;	// Lines till map after last info found
	int		player_count;
	bool	after_map;
}	t_file;

typedef struct s_map
{
	char			**grid;
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
	t_file		file;
	t_player	player;
}	t_cub3d;

// Parser
void	check_file(t_cub3d *cub3d, char *line, int r_code);
int		get_floor_color(t_cub3d *cub3d, char *line, int i);
int		get_ceiling_color(t_cub3d *cub3d, char *line, int i);
void	parse_file(t_cub3d *cub3d, char *input);
void	parse_map(t_cub3d *cub3d);

// Parser Utils
int		check_whitespace(char c);
int		check_identifier(t_cub3d *cub3d, char *line);
void	clear_gnl(t_cub3d *cub3d, int r_code, int error_h);
void	gnl_till_map(t_cub3d *cub3d);
int		check_char(char c, int x);

// Close program
void	close_program(t_cub3d *cub3d, char *msg, int exit_code);
void	error_handler(int i);
void	checkfile_error_handler(int i);
void	parsefile_error_handler(t_cub3d *cub3d, int i);

#endif