
#include "raycaster2.h"

void handle_input2(void *param)
{
    t_game *game = (t_game *)param;

    // Forward/Backward movement
    if (mlx_is_key_down(game->mlx, MLX_KEY_W))
    {
        // Calculate new position
        double new_x = game->player.pos_x + game->player.dir_x * MOVE_SPEED;
        double new_y = game->player.pos_y + game->player.dir_y * MOVE_SPEED;

        // Check for collisions before moving
        // if (game->world_map[(int)game->player.pos_y * game->map_width + (int)new_x] == 0)
            game->player.pos_x = new_x;
        // if (game->world_map[(int)new_y * game->map_width  (int)game->player.pos_x] == 0)
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
		game->player.player_angle -= ROT_SPEED;
		if (game->player.player_angle < 0)
			game->player.player_angle += 360;
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_D))
    {
        // Same rotation matrix but opposite direction
        double old_dir_x = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(ROT_SPEED) - game->player.dir_y * sin(ROT_SPEED);
        game->player.dir_y = old_dir_x * sin(ROT_SPEED) + game->player.dir_y * cos(ROT_SPEED);
		game->player.player_angle += ROT_SPEED;
		if (game->player.player_angle > 360)
			game->player.player_angle -= 360;
    }

    // Exit on ESC
    if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(game->mlx);

    // Update display
    raycast(game);
}
