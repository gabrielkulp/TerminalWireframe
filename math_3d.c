#include <stdlib.h>
#include <math.h>
#include "math_3d.h"

// add two vectors
Vector3 Vector3_add (Vector3 a, Vector3 b) {
	Vector3 c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return c;
}

// multiply two vectors component-wise
Vector3 Vector3_scale (Vector3 a, Vector3 b) {
	Vector3 c;
	c.x = a.x * b.x;
	c.y = a.y * b.y;
	c.z = a.z * b.z;
	return c;
}

// turn euler angles to a 3x3 matrix
void euler_to_Mat3 (Vector3 eul, float mat[3][3]) {
	float ch = cos(-eul.y); // heading = yaw
	float sh = sin(-eul.y);
	float ca = cos(-eul.z); // attitude = pitch
	float sa = sin(-eul.z);
	float cb = cos( eul.x); // bank = roll
	float sb = sin( eul.x);

	mat[0][0] = ch * ca;
	mat[0][1] = sh*sb - ch*sa*cb;
	mat[0][2] = ch*sa*sb + sh*cb;
	mat[1][0] = sa;
	mat[1][1] = ca*cb;
	mat[1][2] = -ca*sb;
	mat[2][0] = -sh*ca;
	mat[2][1] = sh*sa*cb + ch*sb;
	mat[2][2] = -sh*sa*sb + ch*cb;
}

// rotate a vector according to a 3x3 matrix
Vector3 Vector3_rotate (Vector3 a, float mat[3][3]) {
	Vector3 c;

	c.x = a.x*mat[0][0] + a.y*mat[1][0] + a.z*mat[2][0];
	c.y = a.x*mat[0][1] + a.y*mat[1][1] + a.z*mat[2][1];
	c.z = a.x*mat[0][2] + a.y*mat[1][2] + a.z*mat[2][2];
	return c;
}

#define NEAR_CLIP 5
#define FAR_CLIP -15
// scale a point in x and y depending on its z-depth
Vector3 Vector3_perspective (Vector3 a, float p) {
	Vector3 c;
	float z = (a.z - FAR_CLIP) / (NEAR_CLIP - FAR_CLIP);

	c.x = (a.x) / (z);
	c.y = (a.y) / (z);
	c.z = a.z;
	return c;
}

// return an identity transformation
Transform * getDefaultTransform () {
	Transform * t = (Transform*)malloc(sizeof(Transform));
	if (!t) return NULL;
	t->position.x = 0;
	t->position.y = 0;
	t->position.z = 0;
	t->eulerAngles.x = 0;
	t->eulerAngles.y = 0;
	t->eulerAngles.z = 0;
	t->scale.x = 1;
	t->scale.y = 1;
	t->scale.z = 1;
	return t;
}

#define PERSPECTIVE 2.0
// translate all vertices according to a given transform
void transform_points (Transform * t, Vector3 * verticesIn, Vector3 * verticesOut, int num_v) {
	float rotMatrix[3][3];
	euler_to_Mat3(t->eulerAngles, rotMatrix);

	for (int i = 0; i < num_v; i++) {
		// scale
		verticesOut[i] = Vector3_scale(verticesIn[i], t->scale);
		// rotate
		verticesOut[i] = Vector3_rotate(verticesOut[i], rotMatrix);
		// translate
		verticesOut[i] = Vector3_add(verticesOut[i], t->position);
		// perspective projection
		verticesOut[i] = Vector3_perspective(verticesOut[i], PERSPECTIVE);
	}
}
