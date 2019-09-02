#ifndef BUFFER_H
#define BUFFER_H

struct float_buffer {
	float ** values;
	int width;
	int height;
};
typedef struct float_buffer Buffer;

// allocate a new buffer of the specified size
// with uninitialized contents
Buffer * buffer_create (int width, int height);

// free buffer contents and buffer itself
void buffer_free (Buffer * b);

// Copy contents to new size. new spaces are filled with value of fill
Buffer * buffer_resize (Buffer * b, int width_new, int height_new, float fill);

// set contents to all one value
void buffer_fill (Buffer * b, float value);

#endif
