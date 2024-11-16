/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleunin <saleunin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:14:48 by wsonepou          #+#    #+#             */
/*   Updated: 2024/11/15 17:57:45 by saleunin         ###   ########.fr       */
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
// # define TXTR_DIM 500
# define SPEED 0.06
# define PI 3.14159265359

# define COL SPEED + SPEED * 3
// # define COL2 SPEED + SPEED * 2
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
	float		plane_x;
	float		plane_y;
}	t_player;

typedef struct s_file
{
	int		data_c;
	int		NO;
	int		SO;
	int		WE;
	int		EA;
	int		floor;
	int		ceil;
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
	mlx_image_t		*walls;
}	t_map;

typedef struct s_minimap
{
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

enum e_side_hit
{
	vertical,
	horizontal
};

typedef struct s_raycast {
	int				x;
	double			ray_dir_x; //x angle ray travel
	double			ray_dir_y; // y angle ray travel
	int				map_x; // current x coordinate map to check
	int				map_y; // curent y coordinate map to check
	double			wall_dist; // distance to the wall at angle of 90 degrees
	double			side_dist_x; // length between player and x side for first position
	double			side_dist_y; // length between player and y side for first position
	short			step_x; // check if ray is left(-) or right(+)
	short			step_y; // check if ray is down(-) or up(+)
	double			delta_dist_x; // length of one x side to next x side; (1 / ray_dir_x)
	double			delta_dist_y; // length of one y side to next y side; (1 / ray_dir_y)
	int				wall_height; // height of the wall to draw
	int				wall_bottom; // where to start drawing the wall
	int				wall_top; // where to stop drawing the wall
	double			wall_x; //where on wall horizontally was hit
	double			tex_x; //pixel where on texture horizontal wall was hit
	double			tex_y; //pixel where on texture vertical wall was hit
	enum e_side_hit	side_hit; // which side of wall was hit
	mlx_texture_t	*texture; // texture of the wall
	double			tex_step;
}	t_raycast;

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
void	close_program_wrapper(void *param);
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

//render frame
void render_frame(t_cub3d *cub3d);

//calculate ray funcs
void calc_rays(t_cub3d *cub3d, t_raycast *cast);
void calc_step_deltas(t_cub3d *cub3d, t_raycast *cast);
void calc_wall_dist(t_cub3d *cub3d, t_raycast *cast);
void calc_wall(t_cub3d *cub3d, t_raycast *cast);

void trace_ray_path(t_cub3d *cub3d, t_raycast *cast);
#endif