/* raycaster.h */
#ifndef RAYCASTER_H
# define RAYCASTER_H

#include <MLX42/MLX42.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>       // For clock() function
#include <string.h>     // For memset
#include <stdio.h>	  // For sprintf

// Window and game settings
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 640
#define WALL_HEIGHT 64     // Standard wall height
#define FOV 60            // Field of view in degrees
#define MOVE_SPEED 1    // Player movement speed
#define ROT_SPEED 0.05    // Player rotation speed

// FPS counter settings
#define FPS_UPDATE_INTERVAL 0.5  // Update FPS display every 0.5 seconds
#define FPS_FONT_COLOR 0xFFFFFF  // White color for FPS text

// Player structure to store position and direction
typedef struct s_player {
    double pos_x;         // Player X position
    double pos_y;         // Player Y position
    double dir_x;         // X component of direction vector
    double dir_y;         // Y component of direction vector
    double plane_x;       // Camera plane X (for FOV)
    double plane_y;       // Camera plane Y (for FOV)
} t_player;

// Main game structure
// Add these to the game structure
typedef struct s_game {
    mlx_t *mlx;
    mlx_image_t *img;
    mlx_image_t *fps_img;    // New image for FPS display
    t_player player;
    int *world_map;
    int map_width;
    int map_height;
    // FPS tracking
    clock_t last_time;       // Last frame time
    clock_t last_fps_update; // Last FPS counter update
    int frame_count;         // Frames since last FPS update
    double current_fps;      // Current FPS value
} t_game;

/* Function prototypes */
void init_game(t_game *game);
void handle_input(void *param);
void render_frame(t_game *game);
void cleanup(t_game *game);
void update_fps(t_game *game);
#endif