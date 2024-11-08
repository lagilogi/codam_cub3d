
#include "raycaster.h"

void handle_mouse(void *param)
{
	int current_x;
	int current_y;
	double difference;
	t_game *game;

	game = (t_game *)param;
	mlx_get_mouse_pos(game->mlx, &current_x, &current_y);
	mlx_set_mouse_pos(game->mlx, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	if (current_x != WINDOW_WIDTH / 2)
	{
		difference = ((double)current_x - (WINDOW_WIDTH / 2)) / 30 * ROT_SPEED;
		// Rotate direction vector using rotation matrix
        double old_dir_x = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(difference) - game->player.dir_y * sin(difference);
        game->player.dir_y = old_dir_x * sin(difference) + game->player.dir_y * cos(difference);

        // Rotate camera plane
        double old_plane_x = game->player.plane_x;
        game->player.plane_x = game->player.plane_x * cos(difference) - game->player.plane_y * sin(difference);
        game->player.plane_y = old_plane_x * sin(difference) + game->player.plane_y * cos(difference);
	}
}

void handle_input(void *param)
{
    t_game *game = (t_game *)param;

	handle_mouse(param);
	update_fps(game);
    // Forward/Backward movement
    if (mlx_is_key_down(game->mlx, MLX_KEY_W))
    {
        // Calculate new position
        double new_x = game->player.pos_x + game->player.dir_x * MOVE_SPEED;
        double new_y = game->player.pos_y + game->player.dir_y * MOVE_SPEED;

        // Check for collisions before moving
        if (game->world_map[(int)game->player.pos_y * game->map_width + (int)new_x] == 0)
            game->player.pos_x = new_x;
        if (game->world_map[(int)new_y * game->map_width + (int)game->player.pos_x] == 0)
            game->player.pos_y = new_y;
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_S))
    {
        double new_x = game->player.pos_x - game->player.dir_x * MOVE_SPEED;
        double new_y = game->player.pos_y - game->player.dir_y * MOVE_SPEED;
        if (game->world_map[(int)game->player.pos_y * game->map_width + (int)new_x] == 0)
            game->player.pos_x = new_x;
        if (game->world_map[(int)new_y * game->map_width + (int)game->player.pos_x] == 0)
            game->player.pos_y = new_y;
    }

    // Left/Right rotation
    if (mlx_is_key_down(game->mlx, MLX_KEY_A))
    {
        // Rotate direction vector using rotation matrix
        double old_dir_x = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(-ROT_SPEED) - game->player.dir_y * sin(-ROT_SPEED);
        game->player.dir_y = old_dir_x * sin(-ROT_SPEED) + game->player.dir_y * cos(-ROT_SPEED);

        // Rotate camera plane
        double old_plane_x = game->player.plane_x;
        game->player.plane_x = game->player.plane_x * cos(-ROT_SPEED) - game->player.plane_y * sin(-ROT_SPEED);
        game->player.plane_y = old_plane_x * sin(-ROT_SPEED) + game->player.plane_y * cos(-ROT_SPEED);
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_D))
    {
        // Same rotation matrix but opposite direction
        double old_dir_x = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(ROT_SPEED) - game->player.dir_y * sin(ROT_SPEED);
        game->player.dir_y = old_dir_x * sin(ROT_SPEED) + game->player.dir_y * cos(ROT_SPEED);
        double old_plane_x = game->player.plane_x;
        game->player.plane_x = game->player.plane_x * cos(ROT_SPEED) - game->player.plane_y * sin(ROT_SPEED);
        game->player.plane_y = old_plane_x * sin(ROT_SPEED) + game->player.plane_y * cos(ROT_SPEED);
    }

    // Exit on ESC
    if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(game->mlx);

    // Update display
    render_frame(game);
}
