#include "raycaster.h"

// Draw a vertical line on the screen
void draw_vertical_line(mlx_image_t *img, int x, int start, int end, int color)
{
    // Clamp line coordinates to screen bounds
    if (start < 0) start = 0;
    if (end >= WINDOW_HEIGHT) end = WINDOW_HEIGHT - 1;

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
        img->pixels[index + 3] = 255;  // Alpha (fully opaque)
    }
}

void render_frame(t_game *game)
{
    // Cast a ray for each vertical screen column
    for (int x = 0; x < WINDOW_WIDTH; x++)
    {
        // Calculate ray position and direction
        // camera_x is the x-coordinate in camera space (-1 to +1)
        double camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
        double ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
        double ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;

        // Current map position
        int map_x = (int)game->player.pos_x;
        int map_y = (int)game->player.pos_y;

        // Length of ray from current position to next x or y-side
        double side_dist_x;
        double side_dist_y;

        // Length of ray from one grid line to next
        double delta_dist_x = fabs(1 / ray_dir_x);
        double delta_dist_y = fabs(1 / ray_dir_y);

        // Direction to step in (+1 or -1)
        int step_x;
        int step_y;

        // Calculate step direction and initial side distances
        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (game->player.pos_x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - game->player.pos_x) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (game->player.pos_y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - game->player.pos_y) * delta_dist_y;
        }

        // DDA (Digital Differential Analysis) algorithm
        int hit = 0;  // Was a wall hit?
        int side;     // Was it a NS or EW wall hit?
        
        // Step through map until we hit a wall
        while (hit == 0)
        {
            // Jump to next map square in x or y direction
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;  // X wall hit
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;  // Y wall hit
            }
            
            // Check if ray hit a wall
            if (game->world_map[map_y * game->map_width + map_x] > 0)
                hit = 1;
        }

        // Calculate distance to wall (using perpendicular distance to avoid fisheye effect)
        double perp_wall_dist;
        if (side == 0)
            perp_wall_dist = (map_x - game->player.pos_x + (1 - step_x) / 2) / ray_dir_x;
        else
            perp_wall_dist = (map_y - game->player.pos_y + (1 - step_y) / 2) / ray_dir_y;

        // Calculate height of wall slice to draw
        int line_height = (int)(WINDOW_HEIGHT / perp_wall_dist);

        // Calculate lowest and highest pixel of wall slice
        int draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
		printf("draw_start: %d\n", draw_start);
        int draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
		printf("draw_end: %d\n\n", draw_end);
        // Choose wall color (darker for NS walls)
        int color = side == 1 ? 0xFF0000 : 0xCC0000;

        // Draw wall slice
        draw_vertical_line(game->img, x, draw_start, draw_end, color);

        // Draw ceiling (blue sky)
        draw_vertical_line(game->img, x, 0, draw_start, 0x87CEEB);

        // Draw floor (gray)
        draw_vertical_line(game->img, x, draw_end, WINDOW_HEIGHT, 0x808080);
    }
}
