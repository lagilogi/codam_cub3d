#include "raycaster.h"

// Draw a vertical line on the screen
void draw_vertical_line(mlx_image_t *img, int x, int start, int end, int color)
{
	// Clamp line coordinates to screen bounds
	if (start < 0)
		start = 0;
	if (end >= WINDOW_HEIGHT)
		end = WINDOW_HEIGHT - 1;

	// Extract RGB components from color
	// uint8_t r = (color >> 16) & 0xFF;
	// uint8_t g = (color >> 8) & 0xFF;
	// uint8_t b = color & 0xFF;
	// Draw the line pixel by pixel
	for (int y = start; y <= end; y++)
	{
		mlx_put_pixel(img, x, y, color);
		// // Calculate pixel index (4 bytes per pixel: RGBA)
		// int index = (y * img->width + x) * 4; // it is stored bottom to top in index and * 4 is because there are 3 colours and transparency
		// // Set pixel color components
		// img->pixels[index] = r;
		// img->pixels[index + 1] = g;
		// img->pixels[index + 2] = b;
		// img->pixels[index + 3] = 255; // Alpha (fully opaque)
	}
}


void draw_vertical_line_texture(t_game *game, int x, int start, int end,
                       double wall_x, int side)
{
	double tex_pos = 0;
    double step = (double)WALL_HEIGHT / (end - start);
	if (end < WINDOW_HEIGHT)
		tex_pos = 0;
	else
		tex_pos = (end - WINDOW_HEIGHT) * step;
    // Get texture X coordinate
	int tex_x = (int)(wall_x * WALL_HEIGHT);
	if (side == 0 && game->player.dir_x > 0)
		tex_x = WALL_HEIGHT - tex_x - 1;
	if (side == 1 && game->player.dir_y < 0)
		tex_x = WALL_HEIGHT - tex_x - 1;

	// Calculate texture step and starting texture coordinate
	    // Clamp coordinates
    if (start < 0) start = 0;
	if (end >= WINDOW_HEIGHT)
		end = WINDOW_HEIGHT;
	// Draw the textured vertical line
    for (int y = start; y < end; y++)
    {
        int tex_y = (int)tex_pos;
        tex_pos += step;

        // Get texture color
		int index = (WALL_HEIGHT * tex_y + tex_x) * 4;

		uint8_t r = game->wall_image->pixels[index];
		uint8_t g = game->wall_image->pixels[index + 1];
		uint8_t b = game->wall_image->pixels[index + 2];
        // Draw pixel
        index = (y * game->img->width + x) * 4;
        game->img->pixels[index] = r;
        game->img->pixels[index + 1] = g;
        game->img->pixels[index + 2] = b;
        game->img->pixels[index + 3] = 255;
    }
}

void render_frame(t_game *game)
{
	t_raycast cast;
	for (int x = 0; x < WINDOW_WIDTH; x++)
	{
		// calculate ray position and direction
		cast.camera_x = 2 * x / (double)WINDOW_WIDTH - 1; // x-coordinate in camera space left side -1 right side 1
		cast.ray_dir_x = game->player.dir_x + game->player.plane_x * cast.camera_x;
		cast.ray_dir_y = game->player.dir_y + game->player.plane_y * cast.camera_x;

		// which box of the map we're in
		// length of ray from current position to next x or y-side

		cast.map_x = (int)game->player.pos_x;
		cast.map_y = (int)game->player.pos_y;

		// length of ray from one x or y-side to next x or y-side
		cast.delta_dist_x = sqrt(1 + (cast.ray_dir_y * cast.ray_dir_y) / (cast.ray_dir_x * cast.ray_dir_x));
		cast.delta_dist_y = sqrt(1 + (cast.ray_dir_x * cast.ray_dir_x) / (cast.ray_dir_y * cast.ray_dir_y));
		// double cast.delta_dist_x = fabs(1 / cast.ray_dir_x); // get absolute value of x and y
		// double cast.delta_dist_y = fabs(1 / cast.ray_dir_y);

		// what direction to step in x or y-direction (either +1 or -1)



		// calculate step and initial sideDist
		if (cast.ray_dir_x < 0)
		{
			cast.step_x = -1;
			cast.side_dist_x = (game->player.pos_x - cast.map_x) * cast.delta_dist_x;
		}
		else
		{
			cast.step_x = 1;
			cast.side_dist_x = (cast.map_x + 1.0 - game->player.pos_x) * cast.delta_dist_x;
		}
		if (cast.ray_dir_y < 0)
		{
			cast.step_y = -1;
			cast.side_dist_y = (game->player.pos_y - cast.map_y) * cast.delta_dist_y;
		}
		else
		{
			cast.step_y = 1;
			cast.side_dist_y = (cast.map_y + 1.0 - game->player.pos_y) * cast.delta_dist_y;
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
			// Check if ray has hit a wall
			if (game->world_map[cast.map_x + cast.map_y * game->map_width] > 0)
				break ;
		}

		// Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
		if (cast.side_hit == vertical)
			cast.perp_wall_dist = (cast.map_x - game->player.pos_x + (1 - cast.step_x) / 2) / cast.ray_dir_x;
		else
			cast.perp_wall_dist = (cast.map_y - game->player.pos_y + (1 - cast.step_y) / 2) / cast.ray_dir_y;

		// Calculate height of line to draw on screen
		cast.wall_height = (int)(WINDOW_HEIGHT / cast.perp_wall_dist);

		// calculate lowest and highest pixel to fill in current stripe
		cast.wall_top = -cast.wall_height / 2 + WINDOW_HEIGHT / 2;
		// if (cast.wall_top < 0)
		// 	cast.wall_top = 0;
		cast.wall_bottom = cast.wall_height / 2 + WINDOW_HEIGHT / 2;
		// if (cast.wall_bottom >= WINDOW_HEIGHT)
		// 	cast.wall_bottom = WINDOW_HEIGHT - 1;
		double wallX; // where exactly the wall was hit
		if (cast.side_hit == 0)
			wallX = game->player.pos_y + cast.perp_wall_dist * cast.ray_dir_y;
		else
			wallX = game->player.pos_x + cast.perp_wall_dist * cast.ray_dir_x;
		wallX -= floor((wallX));

		draw_vertical_line_texture(game, x, cast.wall_top, cast.wall_bottom, wallX, cast.side_hit);
		draw_vertical_line(game->img, x, 0, cast.wall_top, 0x000000FF);
		draw_vertical_line(game->img, x, cast.wall_bottom, WINDOW_HEIGHT, 0xFFFFFFFF);
	}
}
