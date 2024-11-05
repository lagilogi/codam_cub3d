/* raycaster.h */
#ifndef RAYCASTER2_H
# define RAYCASTER2_H

#include <MLX42/MLX42.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>       // For clock() function
#include <string.h>     // For memset
#include <stdio.h>	  // For sprintf

// Window and game settings
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 1280
#define WALL_DIMENSIONS 60     // Standard wall height
#define MOVE_SPEED 0.2    // Player movement speed
#define ROT_SPEED 0.05    // Player rotation speed
#define PI 3.141592653589793238462643383279


// FPS counter settings
#define FPS_UPDATE_INTERVAL 0.5  // Update FPS display every 0.5 seconds
#define FPS_FONT_COLOR 0xFFFFFF  // White color for FPS text

// Player structure to store position and direction
typedef struct s_player {
    double pos_x;         // Player X position
    double pos_y;         // Player Y position
	double dir_x;
	double dir_y;
	double player_angle; // radians player angle
} t_player;

typedef struct s_file
{
	int		data_c;
	int		map_cols;
	int		map_rows;
	int		NO;
	int		SO;
	int		WE;
	int		EA;
	int		F;
	int		C;
	int		lines_till_map;
	int		player_count;
	bool	after_map;
}	t_file;

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
    mlx_texture_t *wall_texture;
	mlx_image_t *wall_image;
	t_file		file;
} t_game;

enum e_side_hit
{
	vertical,
	horizontal
};

typedef struct s_raycast	t_raycast;

struct s_raycast {
	double			camera_x; // x coordinate in camera space for current width pixel on screen
	double			ray_dir_x; //x angle ray travel
	double			ray_dir_y; // y angle ray travel
	int				map_x; // current x coordinate map to check
	int				map_y; // curent y coordinate map to check
	double			perp_wall_dist; // distance to the wall at angle of 90 degrees
	double			side_dist_x; // length between player and x side for first position
	double			side_dist_y; // length between player and y side for first position
	short			step_x; // check if ray is left(-) or right(+)
	short			step_y; // check if ray is down(-) or up(+)
	double			delta_dist_x; // length of one x side to next x side; (1 / ray_dir_x)
	double			delta_dist_y; // length of one y side to next y side; (1 / ray_dir_y)
	// int				wall dimension; // height of the wall to draw
	int				wall_bottom; // where to start drawing the wall
	int				wall_top; // where to stop drawing the wall
	enum e_side_hit	side_hit;

};

/* Function prototypes */
void init_game(t_game *game);
void handle_input2(void *param);
void render_frame(t_game *game);
void cleanup(t_game *game);
void update_fps(t_game *game);
void raycast(t_game *game);
#endif