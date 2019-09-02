#include <stdlib.h> // malloc, free

#include "buffer.h"

// allocate buffer. Will have uninitialized values
Buffer * buffer_create (int width, int height) {
	if (width  < 0) width  = 0;
	if (height < 0) height = 0;
	Buffer * b = malloc(sizeof(Buffer));
	b->width = width;
	b->height = height;
	b->values = malloc(b->width * sizeof(float *));
	int x;
	for (x = 0; x < b->width; x++)
		b->values[x] = malloc(b->height * sizeof(float));
	return b;
}

// free buffer and its contents
void buffer_free (Buffer * b) {
	while (b->width) {
		free(b->values[--b->width]);
//		b->values[b->width] = NULL;
	}
	free(b->values);
//	b->values = NULL;
	b->height = 0;
	free(b);
}

// shrink or grow buffer. When growing, fill new space with what you want
Buffer * buffer_resize (Buffer * b, int width_new, int height_new, float fill) {
	Buffer * b_new = buffer_create(width_new, height_new);

	int x,y;
	for (x = 0; x < b_new->width; x++)
		for (y = 0; y < b_new->height; y++)
			if (x >= b->width || y >= b->height)
				b_new->values[x][y] = fill;
			else
				b_new->values[x][y] = b->values[x][y];

	buffer_free(b);
	return b_new;
}

// assign value to all elements
void buffer_fill (Buffer * b, float value) {
	int x, y;
	for (y = 0; y < b->height; y++)
		for (x = 0; x < b->width; x++)
			b->values[x][y] = value;
}
