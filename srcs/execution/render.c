#include "cub3d.h"

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

void draw_vertical_line_texture(t_cub3d *cub3d, int x, int start, int end,
                       double wall_x, int side, t_raycast *cast)
{
	double tex_pos;
	double step = (double)TXTR_DIM / (end - start);
	if (end < HEIGHT)
		tex_pos = 0;
	else
		tex_pos = (end - HEIGHT) * step;
	// Get texture X coordinate
	int tex_x = (int)(wall_x * TXTR_DIM);
	if (side == 0 && cast->step_x > 0)
		tex_x = TXTR_DIM - tex_x - 1;
	else if (side == 1 && cast->step_y < 0)
		tex_x = TXTR_DIM - tex_x - 1;


	// Calculate texture step and starting texture coordinate
	// Clamp coordinates
	if (start < 0)
	{
		start = 0;
		end = HEIGHT;
	}
	// Draw the textured vertical line
    for (int y = start; y < end; y++)
    {
        int tex_y = (int)tex_pos;
        tex_pos += step;

        // Get texture color
		int index = (TXTR_DIM * tex_y + tex_x) * 4;

		uint8_t r = cast->texture->pixels[index];
		uint8_t g = cast->texture->pixels[index + 1];
		uint8_t b = cast->texture->pixels[index + 2];
        // Draw pixel
        index = (y * cub3d->map.walls->width + x) * 4;
        cub3d->map.walls->pixels[index] = r;
        cub3d->map.walls->pixels[index + 1] = g;
        cub3d->map.walls->pixels[index + 2] = b;
        cub3d->map.walls->pixels[index + 3] = 255;
    }
}

void render_frame(t_cub3d *cub3d)
{
	t_raycast cast;
	// if (cub3d->map.walls != NULL)
	// 	mlx_delete_image(cub3d->mlx, cub3d->map.walls);

	for (int x = 0; x < WIDTH; x++)
	{
		// calculate ray position and direction
		cast.camera_x = 2 * x / (double)WIDTH - 1; // x-coordinate in camera space left side -1 right side 1
		cast.ray_dir_x = -cub3d->player.delta_x + -cub3d->player.plane_x * cast.camera_x;
		cast.ray_dir_y = -cub3d->player.delta_y + -cub3d->player.plane_y * cast.camera_x;

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
			if (cast.step_x == -1)
				cast.texture = cub3d->map.WE;
			else
				cast.texture = cub3d->map.EA;
			cast.perp_wall_dist = (cast.map_x - cub3d->player.x + (1 - cast.step_x) / 2) / cast.ray_dir_x;
		}
		else
		{
			if (cast.step_y == -1)
				cast.texture = cub3d->map.NO;
			else
				cast.texture = cub3d->map.SO;
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

		draw_vertical_line_texture(cub3d, x, cast.wall_top, cast.wall_bottom, wallX, cast.side_hit, &cast);
		draw_vertical_line(cub3d->map.walls, x, cast.wall_bottom, HEIGHT, (cub3d->map.f_r << 16) + (cub3d->map.f_g << 8) + cub3d->map.f_b);
		draw_vertical_line(cub3d->map.walls, x, 0, cast.wall_top, (cub3d->map.c_r << 16) + (cub3d->map.c_g << 8) + cub3d->map.c_b);
	}
	// mlx_image_to_window(cub3d->mlx, cub3d->map.walls, 0, 0);
}
