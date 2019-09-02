#ifndef MATH_3D_H
#define MATH_3D_H

typedef struct {
	float x, y, z;
} Vector3;

typedef struct Transform {
	Vector3 position, eulerAngles, scale;
} Transform;

typedef struct {
	// indices into vertex array
	int start, end;
} Edge;

// self-explanatory. Details in math_3d.c
Vector3 Vector3_add (Vector3 a, Vector3 b);
Vector3 Vector3_scale (Vector3 a, Vector3 b);
void euler_to_Mat3 (Vector3 eul, float mat[3][3]);
Vector3 Vector3_rotate (Vector3 a, float mat[3][3]);
Vector3 Vector3_perspective (Vector3 a, float p);
Transform * getDefaultTransform ();
void transform_points (Transform * t, Vector3 * verticesIn, Vector3 * verticesOut, int num_v);

#endif
