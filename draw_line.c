
#include <math.h>
#include <graphics.h> // Assuming you have a graphics library

// ...existing code...

void draw_line_with_angle(int x0, int y0, double angle, int length) {
    int x1 = x0 + length * cos(angle);
    int y1 = y0 + length * sin(angle);

    // Function to draw a line from (x0, y0) to (x1, y1)
    draw_line(x0, y0, x1, y1);
}

// ...existing code...