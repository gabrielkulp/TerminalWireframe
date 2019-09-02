#include <stdio.h>   // printf, popen
#include <stdlib.h>  // random, atoi
#include <unistd.h>  // STDIN_FILENO
#include <termios.h> // get and set terminal attributes
#include <stdbool.h> // bool
#include <math.h>    // sqrt

#include "graphics.h" // enum blend_mode

// Height of a character in units of width
#define CHAR_HEIGHT 2.15
// Distance between samples when drawing a line
#define LINE_STEP 0.1

// Characters to print floating-point buffers
const int charnum = 8; // string length
const char * charset = " -~+=o&@";
// alternate charset: " .:%lM@"

// private utilities
inline int _roundF (float x) { return (x < 0) ? (x - 0.5) : (x + 0.5); }
inline int _signF (float x) { return (x > 0) ? 1 : ((x < 0) ? -1 : 0); }
inline int _clamp (int n, int min, int max) { return (n < min) ? min : ((n > max) ? max : n); }
inline float _fclamp (float n, float min, float max) { return (n < min) ? min : ((n > max) ? max : n); }

// public utilities
inline void cursor_move (int x, int y) { printf("\033[%i;%if", y, x); }
inline void screen_clear () { printf("\033[2J"); cursor_move(1,1); }

int _dither (float x) {
	const int dither_steps = 10000;
	int num = _roundF(x);
	float fpart = x - num;

	// take fpart as probability of rounding up
	if ((rand() % dither_steps) <= (fpart * dither_steps * _signF(fpart)))
		return num + _signF(fpart);

	return num;
}

#define BUFFER_SIZE 128
// parses output of system command like tput
int _parse_output (const char * cmd) {
	char buf[BUFFER_SIZE];
	FILE * fp;
	if ((fp = popen(cmd, "r")) == NULL)
		return -1;

	if (fgets(buf, BUFFER_SIZE, fp) != NULL) {
		if (pclose(fp))
			return -1;
		return atoi(buf);
	}

	return 0;
}

// write float to buffer with integer coordinates
void buffer_plot (Buffer * b, int x, int y, float n, enum blend_mode blend) {
	n = _fclamp(n, 0, 1);

	// ignore drawing out-of-bounds
	if (x < 0 || x >= b->width ) return;
	if (y < 0 || y >= b->height) return;

	switch(blend) {
		case blend_alpha_over:
			b->values[x][y] = 1 - ((1 - b->values[x][y]) * (1 - n));
			break;
		case blend_add:
			b->values[x][y] += n;
			break;
		default:
		case blend_overwrite:
			b->values[x][y] = n;
	}
}

// write float to buffer by rounding float coordinates
void buffer_fplot (Buffer * b, float x, float y, float n, enum blend_mode blend) {
	buffer_plot(b, _roundF(x), _roundF(y), n, blend);
}

// print buffer contents to screen
void buffer_flush (Buffer * b, bool dither) {
	cursor_move(0, 0);
	int x, y, c;
	// overwrite top line with blank
	printf("  ");
	for (x = 0; x < b->width; x++)
		printf(" ");
	printf("  ");
	for (y = 0; y < b->height; y++) {
		printf("  "); // left gap
		for (x = 0; x < b->width; x++) {
			if (b->values[x][y] < 0) {
				printf("\033[1C");
				continue;
			}
			if (dither)
				c = _dither(b->values[x][y] * (charnum - 1));
			else
				c = _roundF(b->values[x][y] * (charnum - 1));
			c = _clamp(c, 0, charnum - 1);
			printf("%c", charset[c]);
		}
		printf("  \n");
	}
	fflush(stdout); // show changes immediately
}

// re-evaluate how big the buffer should be, then resize it
Buffer * buffer_fit (Buffer * b, float fill) {
	int cols, lines;
	cols = _parse_output("tput cols") - 4;
	lines= _parse_output("tput lines") - 2;
	return buffer_resize(b, cols, lines, fill);
}

// draw line between two points.
// abstracts coordinates. Origin at terminal center, floating point coords.
void render_line (Buffer * b, float x1, float y1, float x2, float y2) {
	// account for character width
	x1 *= CHAR_HEIGHT;
	x2 *= CHAR_HEIGHT;
	// move origin to the center
	x1 += b->width  / 2; x2 += b->width  / 2;
	y1 += b->height / 2; y2 += b->height / 2;
	float dx = x2 - x1;
	float dy = y2 - y1;
	float dist = sqrt(dx*dx + dy*dy);
	float t, x, y;
	for (t = 0; t <= dist; t+= LINE_STEP) {
		x = ((dx * t)/dist) + x1;
		y = ((dy * t)/dist) + y1;
		buffer_fplot(b, x, y, LINE_STEP, blend_add);
	}
}

// change terminal attributes to be graphics-friendly
void set_canon_echo (bool enable) {
	static bool enabled = true;
	static struct termios old;
	struct termios new;

	if (enable && !enabled) {
		// set terminal attributes to old value
		tcsetattr(STDIN_FILENO, TCSANOW, &old);
		printf("\033[?25h\033[m"); // show cursor
		enabled = true;
	} else if (!enable && enabled) {
		// get current, save it, disable canon and echo, set new
		tcgetattr(STDIN_FILENO, &new);
		old = new;
		new.c_lflag &= (~ICANON & ~ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &new);
		printf("\033[?25l\033[m"); // hide cursor
		enabled = false;
	}
}
