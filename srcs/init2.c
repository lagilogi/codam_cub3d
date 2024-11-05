#include "raycaster2.h"

// Initialize player position and direction
void init_player(t_player *player)
{
    // Start position (2,2)
    player->pos_x = 2;
    player->pos_y = 2;

    // Initial direction vector (looking right)
    player->dir_x = 1;
    player->dir_y = 0;

    // Camera plane perpendicular to direction
    // plane_y = 0.66 gives roughly 66° FOV
	player->player_angle = 0;
}

void init_game(t_game *game)
{
    // Initialize MLX with window settings
    game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Raycaster", false);
    if (!game->mlx)
        exit(1);

    // Create render image
    game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!game->img)
    {
        mlx_terminate(game->mlx);
        exit(1);
    }
    // game->north_texture = mlx_load_png("images/exit.png");
	// game->south_texture = mlx_load_png("images/wall.png");
	// game->east_texture = mlx_load_png("images/path.png");
	// game->west_texture = mlx_load_png("images/exit.png");

	// if (!game->north_texture || !game->south_texture || !game->east_texture || !game->west_texture)
	// 	exit(1);
	// game->wall_image = mlx_texture_to_image(game->mlx, game->wall_texture);
    mlx_image_to_window(game->mlx, game->img, 0, 0);

    // Set up player
    init_player(&game->player);

    // Create map (1 = wall, 0 = empty space)
    game->map_width = 10;
    game->map_height = 10;
    int map[] = {
        1,1,1,1,1,1,1,1,1,1,  // Map border
        1,0,0,0,0,0,0,0,0,1,  // Empty room with walls
        1,0,0,0,0,0,0,0,0,1,
        1,0,0,1,1,0,1,0,0,1,  // Some interior walls
        1,0,0,1,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,1,
        1,0,0,1,0,0,0,0,0,1,
        1,0,0,1,1,0,1,0,0,1,
        1,0,0,0,0,0,0,0,0,1,
        1,1,1,1,1,1,1,1,1,1   // Map border
    };

    // Allocate and copy map data
    game->world_map = malloc(sizeof(int) * game->map_width * game->map_height);
    for (int i = 0; i < game->map_width * game->map_height; i++)
	{
		game->world_map[i] = map[i];
	}
	game->fps_img = mlx_new_image(game->mlx, 50, 20);
    if (!game->fps_img)
    {
        mlx_delete_image(game->mlx, game->img);
        mlx_terminate(game->mlx);
        exit(1);
    }
    mlx_image_to_window(game->mlx, game->fps_img, 10, 10);

    // Initialize FPS tracking
    game->last_time = clock();
    game->last_fps_update = game->last_time;
    game->frame_count = 0;
    game->current_fps = 0.0;

}
