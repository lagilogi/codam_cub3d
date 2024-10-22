#include "raycaster.h"

// Function to draw a character to the FPS image
void draw_char(mlx_image_t *img, int x, int y, char c, int color)
{
    // Simple bitmap font implementation for numbers and decimal point
    // Each number is 3x5 pixels
    const char *patterns[] = {
        "111101101101111", // 0
        "001001001001001", // 1
        "111001111100111", // 2
        "111001111001111", // 3
        "101101111001001", // 4
        "111100111001111", // 5
        "111100111101111", // 6
        "111001001001001", // 7
        "111101111101111", // 8
        "111101111001111", // 9
        "000000010000000"  // .
    };

    int idx = (c == '.') ? 10 : (c - '0');
    if (idx < 0 || idx > 10) return;

    const char *pattern = patterns[idx];
    for (int py = 0; py < 5; py++) {
        for (int px = 0; px < 3; px++) {
            if (pattern[py * 3 + px] == '1') {
                int pos = ((y + py) * img->width + (x + px)) * 4;
                uint8_t r = (color >> 16) & 0xFF;
                uint8_t g = (color >> 8) & 0xFF;
                uint8_t b = color & 0xFF;
                img->pixels[pos] = r;
                img->pixels[pos + 1] = g;
                img->pixels[pos + 2] = b;
                img->pixels[pos + 3] = 255;
            }
        }
    }
}

// Function to draw FPS text
void draw_fps_text(mlx_image_t *img, double fps)
{
    char fps_str[10];
    sprintf(fps_str, "%.1f", fps);

    // Clear the image
    memset(img->pixels, 0, img->width * img->height * 4);

    // Draw "FPS: "
    int x = 5;
    int y = 5;
    
    // Draw the numbers
    for (size_t i = 0; fps_str[i] != '\0'; i++) {
        draw_char(img, x, y, fps_str[i], FPS_FONT_COLOR);
        x += (fps_str[i] == '.') ? 2 : 4;
    }
}

// Function to update FPS counter
void update_fps(t_game *game)
{
    clock_t current_time = clock();
    game->frame_count++;

    // Calculate time elapsed since last FPS update
    double elapsed = (double)(current_time - game->last_fps_update) / CLOCKS_PER_SEC;

    // Update FPS display if interval has passed
    if (elapsed >= FPS_UPDATE_INTERVAL) {
        game->current_fps = game->frame_count / elapsed;
        draw_fps_text(game->fps_img, game->current_fps);
        game->frame_count = 0;
        game->last_fps_update = current_time;
    }

    game->last_time = current_time;
}
