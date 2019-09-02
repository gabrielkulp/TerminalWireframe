#include <stdlib.h> // random
#include <time.h>   // seed random
#include <unistd.h> // usleep
#include <signal.h> // intercept ctrl+C and window resize
#include <stdio.h>  // printf, fflush
#include "graphics.h"
#include "primitives.h"
#include "wireframe.h"

// randomize shading?
#define DITHER true

// flags set by signals SIGWINCH and SIGINT
bool resize = false;
bool quit   = false;

void signal_handler (int signum) {
	// catch each expected signal. Quit on unexpected.
	switch (signum) {
		case SIGWINCH:
			resize = true;
			return;
		case SIGINT:
			quit = true;
			return;
		default:
			set_canon_echo(true);
			fflush(stdout);
			screen_clear();
			printf("Received interrupt %i\n", signum);
			exit(signum);
	}
}

int main () {
	// seed random, register callback handlers
	srand(time(NULL));
	signal(SIGINT,  signal_handler);
	signal(SIGILL,  signal_handler);
	signal(SIGSEGV, signal_handler);
	signal(SIGWINCH,signal_handler);

	// initialize buffer
	Buffer * b = buffer_create(0,0);
	buffer_fill(b, 0);
	b = buffer_fit(b, 0);

	// initialize screen
	set_canon_echo(false);
	screen_clear();

	Wireframe * cube = Primitive_Cube();
	while (!quit) {
		// draw cube, then transform for next frame
		Wireframe_draw(b, cube);
		cube->transform->eulerAngles.x += 0.001;
		cube->transform->eulerAngles.y += 0.002;
		cube->transform->eulerAngles.z += 0.003;

		// respond to SIGWINCH
		if (resize) {
			b = buffer_fit(b, 0);
			resize = false;
			screen_clear();
			continue;
		}

		buffer_flush(b, DITHER); // print
		buffer_fill(b, 0); // clear for next draw

		// TODO: sleep variably to hit target framerate
		usleep(1000);
	}

	// undo screen modifications, free buffer
	set_canon_echo(true);
	Wireframe_free(cube);
	buffer_free(b);
	screen_clear();
	printf("Exited gracefully");
	return 0;
}
