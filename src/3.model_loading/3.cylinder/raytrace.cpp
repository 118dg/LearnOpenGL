#include "raytrace.h"
#include <math.h>

using namespace raytraceData;

raytrace::raytrace(int w, int h)
{
	/* low-level graphics setup */
	lowlevel.initCanvas(w, h);

	/* raytracer setup */
	initCamera(w, h);
	initScene();
}

raytrace::~raytrace()
{
	if (s1 != NULL) delete s1;
	if (viewpoint != NULL) delete viewpoint;
}

GLubyte* raytrace::display(void)
{	
	drawScene();  /* draws the picture in the canvas */

	return lowlevel.flushCanvas();  /* draw the canvas to the OpenGL window */	
}

void raytrace::initScene()
{
	s1 = makeSphere(0.0, 0.0, -2.0, 0.25);
	s1->m = shader.makeMaterial(0.8, 0.1, 0.15, 0.3);

	h1 = makeHalfspace(-3.0f);
	h1->m = shader.makeMaterial(0.5, 0.5, 0.3, 0.3);

	tracer.s1 = s1;
}
void raytrace::initCamera(int w, int h)
{
	viewpoint = makePoint(0.0, 0.0, 0.0, 1.0);
	pnear = -1.0;
	fovx = M_PI / 6;
	/* window dimensions */
	width = w;
	height = h;
}

void raytrace::drawScene(void)
{
	int i, j;
	GLfloat imageWidth;

	/* declare data structures on stack to avoid malloc & free */
	point worldPix;  /* current pixel in world coordinates */
	point direction;
	ray r;
	color c;

	/* z and w are constant for all pixels */
	worldPix.w = 1.0;
	worldPix.z = pnear;

	r.start = &worldPix;
	r.end = &direction;

	imageWidth = 2 * pnear * tan(fovx / 2);

	/* trace a ray for every pixel */
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {

			/* find position of pixel in world coordinates */
			/* y position = (pixel height/middle) scaled to world coords */
			worldPix.y = (j - (height / 2)) * imageWidth / width;
			/* x position = (pixel width/middle) scaled to world coords */
			worldPix.x = (i - (width / 2)) * imageWidth / width;

			/* find direction */
			/* note: direction vector is NOT NORMALIZED */
			calculateDirection(viewpoint, &worldPix, &direction); //ray 방향 결정

			/* Find color for pixel */
			rayColor(&r, &c); // ray를 쏴서 ray와 만나는 곳의 color값을 결정해서 c에 저장
			/* write the pixel! */
			lowlevel.drawPixel(i, j, c.r, c.g, c.b);
		}
	}
}

point* raytrace::makePoint(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	point* p;
	/* allocate memory */	
	p = new point();
	/* put stuff in it */
	p->x = x; p->y = y; p->z = z; p->w = w;
	return (p);
}

sphere* raytrace::makeSphere(GLfloat x, GLfloat y, GLfloat z, GLfloat r) {
	sphere* s;
	/* allocate memory */
	s = new sphere();

	/* put stuff in it */
	s->c = makePoint(x, y, z, 1.0);   /* center */
	s->r = r;   /* radius */
	s->m = NULL;   /* material */
	return(s);
}

halfspace* raytrace::makeHalfspace(GLfloat y) {
	halfspace* plane;
	/* allocate memory */
	plane = new halfspace();

	/* put stuff in it */
	plane->y = y;
	plane->m = NULL;   /* material */
	return(plane);
}

direction* raytrace::makeDirection(GLfloat x, GLfloat y, GLfloat z) {
	direction* dirobj;
	/* allocate memory */
	dirobj = new direction();

	dirobj->x = x;
	dirobj->y = y;
	dirobj->z = z;
	return(dirobj);
}

diffuse* raytrace::makeDiffuse(GLfloat r, GLfloat g, GLfloat b) {
	diffuse* diffobj; 
	/* allocate memory */
	diffobj = new diffuse();

	diffobj->r = r;
	diffobj->g = g;
	diffobj->b = b;
	return(diffobj);
}

specular* raytrace::makeSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat shininess) {
	specular* specobj;
	/* allocate memory */
	specobj = new specular();

	specobj->r = r;
	specobj->g = g;
	specobj->b = b;
	specobj->shininess = shininess;
	return(specobj);
}

intensity* raytrace::makeIntensity(GLfloat r, GLfloat g, GLfloat b) {
	intensity* intensityobj;
	/* allocate memory */
	intensityobj = new intensity();

	intensityobj->r = r;
	intensityobj->g = g;
	intensityobj->b = b;
	return(intensityobj);
}

light* raytrace::makeLight(GLfloat x, GLfloat y, GLfloat z) {
	light* lightobj;
	/* allocate memory */
	lightobj = new light();

	/* put stuff in it */
	lightobj->lightDir = makeDirection(x, y, z);
	lightobj->diff = makeDiffuse(0.8f, 0.8f, 0.8f);
	lightobj->spec = makeSpecular(1.0f, 1.0f, 1.0f,	32.0f);
	lightobj->i = makeIntensity(1.0f, 1.0f, 1.0f);
	return(lightobj);
}

/* returns the color seen by ray r in parameter c */
void raytrace::rayColor(ray* r, color* c) {
	point p;  /* first intersection point */
	vector n;
	material* m;

	light* l1 = makeLight(-3.0f, -5.0f, 0.0f);

	p.w = 0.0;  /* inialize to "no intersection" */
	tracer.trace(r, &p, &n, &m); // ray가 날라가서 어떤 물체와 만나고 그 물체의 normal이 뭔지 계산

	if (p.w != 0.0) { // ray하고 물체가 만나는 곳이 찾아지면 이제 그 곳의 color값 결정
		shader.shade(&p, &n, m, c, l1);  /* do the lighting calculations */
	}
	else {             /* nothing was hit */
		c->r = 0.0;
		c->g = 0.0;
		c->b = 0.0;
	}
}

/* vector from point p to point q is returned in v */
void raytrace::calculateDirection(point* p, point* q, point* v) {
	float length;

	v->x = q->x - p->x;
	v->y = q->y - p->y;
	v->z = q->z - p->z;
	/* a direction is a point at infinity */
	v->w = 0.0;
}
