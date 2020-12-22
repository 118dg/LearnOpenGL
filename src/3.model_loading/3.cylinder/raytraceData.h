#pragma once

#include <glad/glad.h>

/* constants */
#define TRUE 1
#define FALSE 0

#define M_PI 3.1415926535897932384626433832795029

namespace raytraceData {

	/* data structures */
	typedef struct point {
		GLfloat x;
		GLfloat y;
		GLfloat z;
		GLfloat w;
	} point;

	/* a vector is just a point */
	typedef point vector;

	/* a line segment */
	typedef struct segment {
		point* start;
		point* end;
	} segment;

	/* a ray is just a segment with an endpoint at infinity */
	typedef segment ray;

	typedef struct color {
		GLfloat r;
		GLfloat g;
		GLfloat b;
		/* these should be between 0 and 1 */
	} color;

	typedef struct material {
		/* color */
		color c;
		/* ambient reflectivity */
		GLfloat amb;
	} material;

	typedef struct sphere {
		point* c;  /* center */
		GLfloat r;  /* radius */
		material* m;
	} sphere;

	typedef struct halfspace {
		GLfloat y; //xz∆Ú∏È
		material* m;
	};

	typedef struct direction {
		GLfloat x;
		GLfloat y;
		GLfloat z;
	} direction;

	typedef struct diffuse {
		GLfloat r;
		GLfloat g;
		GLfloat b;
	} diffuse;

	typedef struct specular {
		GLfloat r;
		GLfloat g;
		GLfloat b;
		GLfloat shininess;
	} specular;

	typedef struct intensity {
		GLfloat r;
		GLfloat g;
		GLfloat b;
	} intensity;

	typedef struct light {
		direction* lightDir;
		diffuse* diff;
		specular* spec;
		intensity* i;
	} light;
}