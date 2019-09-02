#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "./math_3d.h"
#include "./wireframe.h"

// returns a tetrahedron
Wireframe * Primitive_Tet () {
	Wireframe * w = (Wireframe*)malloc(sizeof(Wireframe));
	w->transform = getDefaultTransform();
	w->transform->scale.x = 7;
	w->transform->scale.y = 7;
	w->transform->scale.z = 7;

	w->num_vertices = 4;
	Vector3 v[] = {
		{.x=.94 , .y=0 ,   .z=-1/3},
		{.x=-.47, .y=.82,  .z=-1/3},
		{.x=-.47, .y=-.82, .z=-1/3},
		{.x=0   , .y=0 ,   .z=1}
	};

	w->num_edges = 6;	
	Edge e[] = {
		{.start=0, .end=1},
		{.start=1, .end=2},
		{.start=2, .end=0},
		{.start=0, .end=3},
		{.start=1, .end=3},
		{.start=2, .end=3}
	};
	
	w->vertices = (Vector3*)malloc(w->num_vertices * sizeof(Vector3));
	w->edges    = (  Edge* )malloc(w->num_edges    * sizeof(Edge));
	int i;
	for (i = 0; i < w->num_vertices; i++)
		w->vertices[i] = v[i];
	for (i = 0; i < w->num_edges; i++)
		w->edges[i] = e[i];
	return w;
}

// returns a quad (square)
Wireframe * Primitive_Quad () {
	Wireframe * w = (Wireframe*)malloc(sizeof(Wireframe));
	w->transform = getDefaultTransform();
	w->transform->scale.x = 3;
	w->transform->scale.y = 3;
	w->transform->scale.z = 3;

	w->num_vertices = 4;
	Vector3 v[] = {
		{.x= 1, .y= 1, .z=0},
		{.x=-1, .y= 1, .z=0},
		{.x=-1, .y=-1, .z=0},
		{.x= 1, .y=-1, .z=0}
	};

	w->num_edges = 5;	
	Edge e[] = {
		{.start=0, .end=1},
		{.start=1, .end=2},
		{.start=2, .end=3},
		{.start=3, .end=0},
		{.start=0, .end=2}
	};
	
	w->vertices = (Vector3*)malloc(w->num_vertices * sizeof(Vector3));
	w->edges    = (  Edge* )malloc(w->num_edges    * sizeof(Edge));
	int i;
	for (i = 0; i < w->num_vertices; i++)
		w->vertices[i] = v[i];
	for (i = 0; i < w->num_edges; i++)
		w->edges[i] = e[i];
	return w;
}

// returns a cube
Wireframe * Primitive_Cube () {
	Wireframe * w = (Wireframe*)malloc(sizeof(Wireframe));
	w->transform = getDefaultTransform();
	w->transform->scale.x = 5;
	w->transform->scale.y = 5;
	w->transform->scale.z = 5;
	w->transform->eulerAngles.x = 0.3;
	w->transform->eulerAngles.y = 0.3;
	w->transform->eulerAngles.z = 0.3;

	w->num_vertices = 8;
	Vector3 v[] = {
		{.x= 1, .y= 1, .z= 1}, // top sq
		{.x=-1, .y= 1, .z= 1},
		{.x=-1, .y=-1, .z= 1},
		{.x= 1, .y=-1, .z= 1},
		{.x= 1, .y= 1, .z=-1}, // bottom sq
		{.x=-1, .y= 1, .z=-1},
		{.x=-1, .y=-1, .z=-1},
		{.x= 1, .y=-1, .z=-1}
	};

	w->num_edges = 12;
	Edge e[] = {
		{.start=0, .end=1}, // top sq
		{.start=1, .end=2},
		{.start=2, .end=3},
		{.start=3, .end=0},
		{.start=4, .end=5}, // bottom sq
		{.start=5, .end=6},
		{.start=6, .end=7},
		{.start=7, .end=4},
		{.start=0, .end=4}, // connectors
		{.start=1, .end=5},
		{.start=2, .end=6},
		{.start=3, .end=7},
	};
	
	w->vertices = (Vector3*)malloc(w->num_vertices * sizeof(Vector3));
	w->edges    = (  Edge* )malloc(w->num_edges    * sizeof(Edge));
	int i;
	for (i = 0; i < w->num_vertices; i++)
		w->vertices[i] = v[i];
	for (i = 0; i < w->num_edges; i++)
		w->edges[i] = e[i];
	return w;
}

#endif
