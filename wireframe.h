#ifndef WIREFRAME_H
#define WIREFRAME_H

#include "./buffer.h"
#include "./math_3d.h"

typedef struct {
	Vector3 * vertices;
	int num_vertices;
	Edge * edges;
	int num_edges;
	Transform * transform;
} Wireframe;

// self-explanatory. Details in wireframe.c
void transform_points (Transform * t, Vector3 * verticesIn, Vector3 * verticesOut, int num_v);
Wireframe * Wireframe_copy (Wireframe * m);
void Wireframe_free (Wireframe * m);
void Wireframe_draw (Buffer * b, Wireframe * m);

#endif
