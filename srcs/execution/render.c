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

void draw_vertical_line_texture(t_cub3d *cub3d, t_raycast *cast)
{
	const int txtr_width = cast->texture->width;
	int	y;
	int	index;

	if (cast->wall_top < 0 || cast->wall_bottom >= HEIGHT)
	{
		cast->wall_top = 0;
		cast->wall_bottom = HEIGHT - 1;
	}
	y = cast->wall_top;
	while (y < cast->wall_bottom)
	{
		index = (txtr_width * (int)cast->tex_y + (int)cast->tex_x) * 4;
		uint8_t r = cast->texture->pixels[index];
		uint8_t g = cast->texture->pixels[index + 1];
		uint8_t b = cast->texture->pixels[index + 2];
		index = (y * cub3d->map.walls->width + cast->x) * 4;
		cub3d->map.walls->pixels[index] = r;
		cub3d->map.walls->pixels[index + 1] = g;
		cub3d->map.walls->pixels[index + 2] = b;
		cub3d->map.walls->pixels[index + 3] = 255;
		cast->tex_y += cast->tex_step;
		y++;
	}
}

void render_frame(t_cub3d *cub3d)
{
	t_raycast cast;
	ft_bzero(&cast, sizeof(t_raycast));
	while (cast.x < WIDTH)
	{

		cast.map_x = (int)cub3d->player.x;
		cast.map_y = (int)cub3d->player.y;
		calc_rays(cub3d, &cast);
		calc_step_deltas(cub3d, &cast);
		trace_ray_path(cub3d, &cast);
		calc_wall_dist(cub3d, &cast);
		calc_wall(cub3d, &cast);
		draw_vertical_line_texture(cub3d, &cast);
		draw_vertical_line(cub3d->map.walls, cast.x, cast.wall_bottom, HEIGHT, (cub3d->map.f_r << 16) + (cub3d->map.f_g << 8) + cub3d->map.f_b);
		draw_vertical_line(cub3d->map.walls, cast.x, 0, cast.wall_top, (cub3d->map.c_r << 16) + (cub3d->map.c_g << 8) + cub3d->map.c_b);
		++cast.x;
	}
}

