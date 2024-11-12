/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/21 13:14:48 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/11/12 18:13:14 by wsonepou      ########   odam.nl         */
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
# define WIDTH 1920
# define HEIGHT 1080
# define DIM 40
# define SPEED 0.05
# define PI 3.14159265359

# define COL SPEED + SPEED * 3
# define COL2 SPEED + SPEED * 2
# define MAPSIZE 320
# define OFFSET 10
// # define ACC 2 	<--- Has to do with Version 2 of collision

typedef struct s_player
{
	float		x;
	float		delta_x;
	float		y;
	float		delta_y;
	float		angle;
}	t_player;

typedef struct s_file
{
	int		data_c;
	int		map_cols;
	int		map_rows;
	int		NO;
	int		SO;
	int		WE;
	int		EA;
	int		F;
	int		C;
	int		lines_till_map;
	int		player_count;
	bool	after_map;
}	t_file;

typedef struct s_map
{
	char			**grid;
	int				cols;
	int				rows;
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

typedef struct s_minimap
{
	mlx_image_t	*f;
	mlx_image_t	*w;
	mlx_image_t	*p;
	mlx_image_t	*r;
	mlx_image_t	*map;
	int			my;
	int			mx;
}	t_minimap;

typedef struct s_cub3d
{
	mlx_t		*mlx;
	int			map_fd;
	t_map		map;
	t_minimap	mini;
	t_file		file;
	t_player	player;
	bool		moving;
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

// Execution
void	starting_exec(t_cub3d *cub3d);
void	user_input(void *param);

// Close program
void	close_program(t_cub3d *cub3d, int exit_code);
void	error_handler(int i);
void	checkfile_error_handler(int i);
void	parsefile_error_handler(t_cub3d *cub3d, int i);
void	execution_error_handler(t_cub3d *cub3d, int i);

// Bonus
// void	create_minimap(t_cub3d *cub3d);
bool	collision_check(t_cub3d *cub3d, char c);
bool	out_of_bounds(t_cub3d *cub3d, int y, int x);

// void	draw_minimap(t_cub3d *cub3d, mlx_t *mlx);
void	create_minimap(t_cub3d *cub3d, mlx_t *mlx);
// void	draw_player(t_cub3d *cub3d, mlx_t *mlx, int y, int x);

#endif