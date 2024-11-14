/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redraw.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/08 14:54:05 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/11/08 16:21:29 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <math.h>

void draw_vertical_line(mlx_image_t *img, int x, int start, int end, int color)
{
	// Clamp line coordinates to screen bounds
	if (start < 0)
		start = 0;
	if (end >= HEIGHT)
		end = HEIGHT - 1;

	// if ()
	// Extract RGB components from color
	uint8_t r = (color >> 16) & 0xFF;
	uint8_t g = (color >> 8) & 0xFF;
	uint8_t b = color & 0xFF;
	// Draw the line pixel by pixel
	for (int y = start; y <= end; y++)
	{
		// mlx_put_pixel(img, x, y, color);
		// // Calculate pixel index (4 bytes per pixel: RGBA)
		int index = (y * img->width + x) * 4; // it is stored bottom to top in index and * 4 is because there are 3 colours and transparency
		// // Set pixel color components
		img->pixels[index] = r;
		img->pixels[index + 1] = g;
		img->pixels[index + 2] = b;
		img->pixels[index + 3] = 255; // Alpha (fully opaque)
	}
}

void drawline(t_cub3d *cub3d, float delta_dist_x, float delta_dist_y, float perp_wall_dist, t_raycast cast)
{
	// const float delta_dist_x = sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x));
	// const float delta_dist_y = sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x));
	int pixel_x = (cub3d->player.x + 0.25) * DIM;
	int pixel_y = (cub3d->player.y + 0.25) * DIM;

	float total_x;
	float total_y;
	float i = 0;
	total_x = 0;
	total_y = 0;
	int step_x;
	int step_y;
	if (cast.ray_dir_x < 0)
	{
		step_x = -1;
	}
	else
	{
		step_x = 1;
	}
	if (cast.ray_dir_y < 0)
	{
		step_y = -1;
	}
	else
	{
		step_y = 1;
	}
	(void)perp_wall_dist;
	while ((float)i < perp_wall_dist * DIM)
	{
		if (total_x + delta_dist_x < total_y + delta_dist_y)
		{
			total_x += delta_dist_x;
			pixel_x += step_x;
		}
		else
		{
			total_y += delta_dist_y;
			pixel_y += step_y;
		}
		if (pixel_x < 0 || pixel_x >= WIDTH || pixel_y < 0 || pixel_y >= HEIGHT)
			break ;
		mlx_put_pixel(cub3d->rays_minimap_img, pixel_x, pixel_y, 0xFF0000FF);
		// printf("x: %d, y: %d\n", pixel_x, pixel_y);
		++i;
	}
}

void draw_rays(t_cub3d *cub3d, mlx_t *mlx)
{
	// if (cub3d->rays_minimap_img != NULL)
	// 	mlx_delete_image(mlx, cub3d->rays_minimap_img);
	// cub3d->rays_minimap_img  = mlx_new_image(mlx, WIDTH, HEIGHT);
	// mlx_image_to_window(mlx, cub3d->rays_minimap_img, 0, 0);
	if (cub3d->render_img)
		mlx_delete_image(mlx, cub3d->render_img);
	cub3d->render_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, cub3d->render_img, 300, 300);
	if (cub3d->rays_minimap_img)
		mlx_delete_image(mlx, cub3d->rays_minimap_img);
	cub3d->rays_minimap_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, cub3d->rays_minimap_img, 0, 0);
	t_raycast cast;
	for (int x = 0; x < WIDTH; x++)
	{
		// calculate ray position and direction
		cast.camera_x = 2 * x / (double)WIDTH - 1; // x-coordinate in camera space left side -1 right side 1
		cast.ray_dir_x = cub3d->player.delta_x + cub3d->player.plane_x * cast.camera_x;
		cast.ray_dir_y = cub3d->player.delta_y + cub3d->player.plane_y * cast.camera_x;

		// which box of the map we're in
		// length of ray from current position to next x or y-side

		cast.map_x = (int)cub3d->player.x;
		cast.map_y = (int)cub3d->player.y;

		// length of ray from one x or y-side to next x or y-side
		cast.delta_dist_x = sqrt(1 + (cast.ray_dir_y * cast.ray_dir_y) / (cast.ray_dir_x * cast.ray_dir_x));
		cast.delta_dist_y = sqrt(1 + (cast.ray_dir_x * cast.ray_dir_x) / (cast.ray_dir_y * cast.ray_dir_y));
		// calculate step and initial sideDist
		if (cast.ray_dir_x < 0)
		{
			cast.step_x = -1;
			cast.side_dist_x = (cub3d->player.x - cast.map_x) * cast.delta_dist_x;
		}
		else
		{
			cast.step_x = 1;
			cast.side_dist_x = (cast.map_x + 1.0 - cub3d->player.x) * cast.delta_dist_x;
		}
		if (cast.ray_dir_y < 0)
		{
			cast.step_y = -1;
			cast.side_dist_y = (cub3d->player.y - cast.map_y) * cast.delta_dist_y;
		}
		else
		{
			cast.step_y = 1;
			cast.side_dist_y = (cast.map_y + 1.0 - cub3d->player.y) * cast.delta_dist_y;
		}
		// perform DDA

		// int hit = 0; // was there a wall hit?
		while (1)
		{
			// jump to next map square, OR in x-direction, OR in y-direction
			if (cast.side_dist_x < cast.side_dist_y)
			{
				cast.side_dist_x += cast.delta_dist_x;
				cast.map_x += cast.step_x;
				cast.side_hit = vertical;
			}
			else
			{
				cast.side_dist_y += cast.delta_dist_y;
				cast.map_y += cast.step_y;
				cast.side_hit = horizontal;
			}
			if (cast.map_y > cub3d->map.rows || cast.map_x > cub3d->map.cols || cast.map_y < 0 || cast.map_x < 0)
				break ;
			// Check if ray has hit a wall
			if (cub3d->map.grid[cast.map_y][cast.map_x] == '1')
			{
				// double angle = atan2(cast.map_y - cub3d->player.y, cast.map_x - cub3d->player.x);
				// double length = sqrt(pow(cast.map_x - cub3d->player.x, 2) + pow(cast.map_y - cub3d->player.y, 2));
				// drawLine(*cub3d, cub3d->player.x, cub3d->player.y, angle, length, cub3d->rays_minimap_img);
				break ;
			}
		}
		// Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
		if (cast.side_hit == vertical)
		{
			// if (cast.step_x == -1)
			// 	cast.texture = game->west_texture;
			// else
			// 	cast.texture = game->east_texture;
			cast.perp_wall_dist = (cast.map_x - cub3d->player.x + (1 - cast.step_x) / 2) / cast.ray_dir_x;
		}
		else
		{
			// if (cast.step_y == -1)
			// 	cast.texture = game->south_texture;
			// else
			// 	cast.texture = game->north_texture;
			cast.perp_wall_dist = (cast.map_y - cub3d->player.y + (1 - cast.step_y) / 2) / cast.ray_dir_y;
		}

		// Calculate height of line to draw on screen
		cast.wall_height = (int)(HEIGHT / cast.perp_wall_dist);

		// calculate lowest and highest pixel to fill in current stripe
		cast.wall_top = -cast.wall_height / 2 + HEIGHT / 2;
		// if (cast.wall_top < 0)
		// 	cast.wall_top = 0;
		cast.wall_bottom = cast.wall_height / 2 + HEIGHT / 2;
		// if (cast.wall_bottom >= HEIGHT)
		// 	cast.wall_bottom = HEIGHT - 1;
		double wallX; // where exactly the wall was hit
		if (cast.side_hit == 0)
			wallX = cub3d->player.y + cast.perp_wall_dist * cast.ray_dir_y;
		else
			wallX = cub3d->player.x + cast.perp_wall_dist * cast.ray_dir_x;
		wallX -= floor((wallX));

		if (x % 50 == 0)
		{
			float wall_dist   = sqrt(pow(cast.map_x - cub3d->player.x, 2) + pow(cast.map_y - cub3d->player.y, 2));
			// if (cast.side_hit == 0 && cast.ray_dir_x > 0)
			// 	wall_dist = sqrt(pow(cast.map_x - cub3d->player.x, 2) + pow(cast.map_y - cub3d->player.y, 2)) + wallX;
			// else if (cast.side_hit == 0 && cast.ray_dir_x < 0)
			// 	wall_dist = sqrt(pow(cast.map_x - cub3d->player.x, 2) + pow(cast.map_y - cub3d->player.y, 2)) + (1 - wallX);
			// else if (cast.side_hit == 1 && cast.ray_dir_y > 0)
			// 	wall_dist = sqrt(pow(cast.map_x - cub3d->player.x, 2) + pow(cast.map_y - cub3d->player.y, 2)) + wallX;
			// else
			// 	wall_dist = sqrt(pow(cast.map_x - cub3d->player.x, 2) + pow(cast.map_y - cub3d->player.y, 2)) + (1 - wallX);
			printf("%f\n", wall_dist);
			drawline(cub3d, cast.delta_dist_x, cast.delta_dist_y, wall_dist, cast);
		}

		// draw_vertical_line_texture(game, x, cast.wall_top, cast.wall_bottom, wallX, cast.side_hit, &cast);
		draw_vertical_line(cub3d->render_img, x, cast.wall_top, cast.wall_bottom, 0xFFFF00);
		draw_vertical_line(cub3d->render_img, x, 0, cast.wall_top, 0x000000);
		draw_vertical_line(cub3d->render_img, x, cast.wall_bottom, HEIGHT, 0xFFFFFF);
	}
}
void	redraw_player(t_cub3d *cub3d, mlx_t *mlx, int y, int x)
{
	int	px;
	int	py;

	if (cub3d->mini.p != NULL)
		mlx_delete_image(cub3d->mlx, cub3d->mini.p);
	cub3d->mini.p = mlx_new_image(mlx, DIM / 2, DIM / 2);
	while (y < DIM / 2)
	{
		while (x < DIM / 2)
		{
			mlx_put_pixel(cub3d->mini.p, x, y, 0x00FF00FF);
			x++;
		}
		x = 0;
		y++;
	}
	px = DIM * (cub3d->player.x + 0.25);
	py = DIM * (cub3d->player.y + 0.25);
	if (mlx_image_to_window(mlx, cub3d->mini.p, px, py) == -1)
		execution_error_handler(cub3d, 3);
	draw_rays(cub3d, mlx);
}
