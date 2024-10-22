

/* main.c */
#include "raycaster.h"

int main(void)
{
    t_game game;

    // Initialize game resources
    init_game(&game);
    
    // Set up game loop with input handling
    mlx_loop_hook(game.mlx, handle_input, &game);
    mlx_loop(game.mlx);
    
    // Clean up resources
    cleanup(&game);
    return (0);
}

/* init.c */

/* render.c */

/* cleanup.c */
#include "raycaster.h"

void cleanup(t_game *game)
{
    // Free allocated resources
    free(game->world_map);
    mlx_delete_image(game->mlx, game->img);
    mlx_terminate(game->mlx);
}