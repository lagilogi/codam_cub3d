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
	uint8_t r = (color >> 16) & 0xFF;
	uint8_t g = (color >> 8) & 0xFF;
	uint8_t b = color & 0xFF;
	// Draw the line pixel by pixel
	for (int y = start; y <= end; y++)
	{
		// Calculate pixel index (4 bytes per pixel: RGBA)
		int index = (y * img->width + x) * 4; // it is stored bottom to top in index and * 4 is because there are 3 colours and transparency
		// Set pixel color components
		img->pixels[index] = r;
		img->pixels[index + 1] = g;
		img->pixels[index + 2] = b;
		img->pixels[index + 3] = 255; // Alpha (fully opaque)
	}
}

#define TEX_WIDTH 60
#define TEX_HEIGHT 60

void draw_vertical_line_texture(t_game *game, int x, int start, int end,
                       double wall_x, int side)
{
    // Clamp coordinates
    if (start < 0) start = 0;
    if (end >= WINDOW_HEIGHT) end = WINDOW_HEIGHT - 1;

	// wall_x = 0.4;
    // Get texture X coordinate
	int tex_x = (int)(wall_x * TEX_WIDTH);
	if (side == 0 && game->player.dir_x > 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	if (side == 1 && game->player.dir_y < 0)
		tex_x = TEX_WIDTH - tex_x - 1;

	// Calculate texture step and starting texture coordinate
    double step = (double)TEX_HEIGHT / (end - start);
    double tex_pos = (start - WINDOW_HEIGHT / 2 + (end - start) / 2) * step;

    // Draw the textured vertical line
    for (int y = start; y < end; y++)
    {
        int tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
        tex_pos += step;

        // Get texture color
		int index = (TEX_HEIGHT * tex_y + tex_x) * 4;

		uint8_t r = game->wall_image->pixels[index];
		uint8_t g = game->wall_image->pixels[index + 1];
		uint8_t b = game->wall_image->pixels[index + 2];
		// uint8_t a = game->wall_texture->pixels[index + 3];

		// unsigned int color = r << 24 | g << 16 | b << 8 | a;

        // // Darken colors for y-sides (simple shading)
        // if (side == 1)
        // {
        //     r = r * 0.7;
		// 	b = b * 0.7;
		// 	g = g * 0.7;
        //     // color = (r << 16) | (g << 8) | b;
        // }

        // Draw pixel
        index = (y * game->img->width + x) * 4;
        game->img->pixels[index] = r;
        game->img->pixels[index + 1] = g;
        game->img->pixels[index + 2] = b;
        game->img->pixels[index + 3] = 255;
    }
}

#define texture_height 60
#define texture_width 60

void render_frame(t_game *game)
{


	for (int x = 0; x < WINDOW_WIDTH; x++)
	{
		// calculate ray position and direction
		double cameraX = 2 * x / (double)WINDOW_WIDTH - 1; // x-coordinate in camera space left side -1 right side 1
		double rayDirX = game->player.dir_x + game->player.plane_x * cameraX;
		double rayDirY = game->player.dir_y + game->player.plane_y * cameraX;

		// which box of the map we're in
		// length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		int mapX = (int)game->player.pos_x;
		int mapY = (int)game->player.pos_y;

		// length of ray from one x or y-side to next x or y-side
		double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		// double deltaDistX = fabs(1 / rayDirX); // get absolute value of x and y
		// double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		// what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;



		// calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game->player.pos_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->player.pos_x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->player.pos_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->player.pos_y) * deltaDistY;
		}
		// perform DDA

		int hit = 0; // was there a wall hit?
		int side;	 // was a NS or a EW wall hit?
		while (hit == false)
		{
			// jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			// Check if ray has hit a wall
			if (game->world_map[mapX + mapY * game->map_width] > 0)
				hit = true;
		}

		// Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
		if (side == 0)
			perpWallDist = (mapX - game->player.pos_x + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - game->player.pos_y + (1 - stepY) / 2) / rayDirY;

		// Calculate height of line to draw on screen
		int lineHeight = (int)(WINDOW_HEIGHT / perpWallDist);

		// calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + WINDOW_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + WINDOW_HEIGHT / 2;
		if (drawEnd >= WINDOW_HEIGHT)
			drawEnd = WINDOW_HEIGHT - 1;
		double wallX; // where exactly the wall was hit
		if (side == 0)
			wallX = game->player.pos_y + perpWallDist * rayDirY;
		else
			wallX = game->player.pos_x + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		draw_vertical_line_texture(game, x, drawStart, drawEnd, wallX, side);
		draw_vertical_line(game->img, x, 0, drawStart, 0x87CEEB);
		draw_vertical_line(game->img, x, drawEnd, WINDOW_HEIGHT, 0x808080);
	}
}
