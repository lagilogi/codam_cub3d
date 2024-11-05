#include "raycaster2.h"

static void draw_vertical_line_2(mlx_image_t *img, int x, int start, int end, int color)
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
float calc_distance(float x1, float y1, float x2, float y2, float ray_angle)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

#define FOV_ANGLE 60


void raycast(t_game *game)
{
	// t_raycast cast;

	double player_pos_x = game->player.pos_x * 64;
	double player_pos_y = game->player.pos_y * 64;

	int r;
	int map_x;
	int map_y;
	int mp;
	int max_depth_check;

	float ray_x;
	float ray_y;
	float ray_angle;
	float x_offset;
	float y_offset;
	float hx;
	float hy;
	float vx;
	float vy;

	float dis_hor = 1000000000;
	float dis_ver = 1000000000;
	ray_angle = game->player.player_angle - (FOV_ANGLE / 2);
	if (ray_angle < 0)
		ray_angle += 360;

	for (r = 0; r < WINDOW_WIDTH; r++)
	{
		ray_angle *= 0.01745329252;
		max_depth_check = 0;
		float a_tan = -1 / tan(ray_angle);
		if (ray_angle > PI) // looking down
		{
			ray_y = (((int)player_pos_y >> 6) << 6) - 0.0001;
			ray_x = (player_pos_y - ray_y) * a_tan + player_pos_x;
			y_offset = -64;
			x_offset = y_offset * a_tan;
		}
		if (ray_angle < PI) // looking up
		{
			ray_y = (((int)player_pos_y >> 6) << 6) + 64;
			ray_x = (player_pos_y - ray_y) * a_tan + player_pos_x;
			y_offset = 64;
			x_offset = y_offset * a_tan;
		}
		if (ray_angle == 0 || ray_angle == PI)
		{
			max_depth_check = 100;
			ray_x = game->player.pos_x;
			ray_y = game->player.pos_y;
		}
		while (max_depth_check < 100)
		{
			map_x = (int)ray_x >> 6;
			map_y = (int)ray_y >> 6;
			int mp = map_y * game->map_width + map_x;
			if (map_x > game->map_width || map_y > game->map_height)
				max_depth_check = 200;
			else if (game->world_map[mp] == 1)
			{
				dis_hor = calc_distance(player_pos_x, player_pos_y, ray_x, ray_y, ray_angle);
				hx = ray_x;
				hy = ray_y;
				max_depth_check = 100;
			}
			else
			{
				ray_x += x_offset;
				ray_y += y_offset;
				++max_depth_check;
			}
		}
		//-------check vertical intersections
		max_depth_check = 0;
		float n_tan = -tan(ray_angle);
		if (ray_angle > PI / 2 && ray_angle < 3 * PI / 2) // looking left
		{
			ray_x = (((int)player_pos_x >> 6) << 6) - 0.0001;
			ray_y = (player_pos_x - ray_x) * n_tan + player_pos_y;
			x_offset = -64;
			y_offset = x_offset * n_tan;
		}
		if (ray_angle < PI / 2 || ray_angle > 3 * PI / 2) // looking right
		{
			ray_x = (((int)player_pos_x >> 6) << 6) + 64;
			ray_y = (player_pos_x - ray_x) * n_tan + player_pos_y;
			x_offset = 64;
			y_offset = x_offset * n_tan;
		}
		if (ray_angle == PI / 2 || ray_angle == 3 * PI / 2) // looking straight up or down
		{
			max_depth_check = 100;
			ray_x = game->player.pos_x;
			ray_y = game->player.pos_y;
		}
		while (max_depth_check < 100)
		{
			map_x = (int)ray_x >> 6;
			map_y = (int)ray_y >> 6;
			int mp = map_y * game->map_width + map_x;
			if (map_x > game->map_width || map_y > game->map_height)
				max_depth_check = 200;
			else if (game->world_map[mp] == 1)
			{
				dis_ver = calc_distance(player_pos_x, player_pos_y, ray_x, ray_y, ray_angle);
				vx = ray_x;
				vy = ray_y;
				max_depth_check = 100;
			}
			else
			{
				ray_x += x_offset;
				ray_y += y_offset;
				++max_depth_check;
			}
		}
		ray_angle += PI * 2 / 3 / WINDOW_WIDTH;
		float dis;
		float wall_x;
		float wall_y;
		if (dis_hor < dis_ver)
		{
			dis = dis_hor;
			wall_x = hx;
			wall_y = hy;
		}
		else
		{
			dis = dis_ver;
			wall_x = vx;
			wall_y = vy;
		}
		int wall_height = (int)(WINDOW_HEIGHT / dis);
		int start = -wall_height / 2 + WINDOW_HEIGHT / 2;
		int end = wall_height / 2 + WINDOW_HEIGHT / 2;
		draw_vertical_line_2(game->img, r, start, end, 0x00FF00);
		draw_vertical_line_2(game->img, r, start, start + 1, 0xFF0000);
		draw_vertical_line_2(game->img, r, end, end + 1, 0xFF0000);
	}
}
