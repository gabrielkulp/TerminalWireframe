#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdbool.h>
#include "buffer.h"

enum blend_mode {
	blend_overwrite,
	blend_alpha_over,
	blend_add,
};

// set a 0-1 value at coordinates.
// blend = true will alpha-over the previous value at that spot
// blend = false will overwrite previous value
void buffer_plot (Buffer * b, int x, int y, float n, enum blend_mode blend);

// same thing but float coords are rounded to int first
void buffer_fplot (Buffer * b, float x, float y, float n, enum blend_mode blend);

// move the cursor to a new location. x is column, y is row, origin in upper-left
void cursor_move (int x, int y);

// print the buffer to the upper-left on the console
// dither=true to randomly dither the output
void buffer_flush (Buffer * b, bool dither);

// resize the buffer to fit the screen
Buffer * buffer_fit (Buffer * b, float fill);

// draw a smooth line between (x1, y1) and (x2, y2)
void render_line (Buffer * b, float x1, float y1, float x2, float y2);

// clear screen and move cursor back to origin
void screen_clear ();

// enable or disable line buffering and keypress echoing
void set_canon_echo (bool enable);

#endif
