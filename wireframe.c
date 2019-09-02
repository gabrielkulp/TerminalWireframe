#include <stdlib.h>
#include "./wireframe.h"
#include "./buffer.h"
#include "./graphics.h"
#include "./math_3d.h"

// return a deep copy of the specified wireframe
Wireframe * Wireframe_copy (Wireframe * m) {
	Wireframe * m2 = (Wireframe*)malloc(sizeof(Wireframe));
	*m2 = *m;

	m2->vertices = (Vector3*)malloc(m2->num_vertices * sizeof(Vector3));
	m2->edges    = (  Edge* )malloc(m2->num_edges    * sizeof(Edge));
	m2->transform = (Transform*)malloc(sizeof(Transform));	

	if (!m2->vertices || !m2->edges || !m2->transform)
		return NULL;

	int i;
	for (i = 0; i < m2->num_vertices; i++) {
		m2->vertices[i] = m->vertices[i];
	}

	for (i = 0; i < m2->num_edges; i++) {
		m2->edges[i] = m->edges[i];
	}

	*(m2->transform) = *(m->transform);

	return m2;
}

// free the specified wireframe
void Wireframe_free (Wireframe * m) {
	free(m->vertices);
	m->vertices = (Vector3*)0;
	m->vertices = NULL;
	m->num_vertices = 0;

	free(m->edges);
	m->edges = (Edge*)0;
	m->edges = NULL;
	m->num_edges = 0;

	free(m->transform);

	free(m);
}

// transform and plot a wireframe on a buffer
void Wireframe_draw (Buffer * b, Wireframe * m) {
	Vector3 * transVert = (Vector3*)malloc(m->num_vertices * sizeof(Vector3));
	if (!transVert) return;

	transform_points(m->transform, m->vertices, transVert, m->num_vertices);
	
	for (int i = 0; i < m->num_edges; i++) {
		render_line(b,
			(transVert + m->edges[i].start)->x,
			(transVert + m->edges[i].start)->y,
			(transVert + m->edges[i].end)->x,
			(transVert + m->edges[i].end)->y
		);
	}
	free(transVert);
}
