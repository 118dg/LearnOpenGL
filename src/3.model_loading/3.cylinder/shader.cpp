#include "shader.h"
#include "math.h"

using namespace raytraceData;

shader::shader()
{
}

shader::~shader()
{
}

material* shader::makeMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat amb) {
	material* m;

	/* allocate memory */
	m = new material();

	/* put stuff in it */
	m->c.r = r;
	m->c.g = g;
	m->c.b = b;
	m->amb = amb;
	return(m);
}

/* LIGHTING CALCULATIONS */

/* shade */
/* color of point p with normal vector n and material m returned in c */
void shader::shade(point* p, vector* n, material* m, color* c, light* l1) {

	// normalize N
	GLfloat n_size = sqrt((double)n->x * n->x + (double)n->y * n->y + (double)n->z * n->z);
	n->x = n->x / n_size;
	n->y = n->y / n_size;
	n->z = n->z / n_size;

	vector L;
	L.x = l1->lightDir->x - p->x;
	L.y = l1->lightDir->y - p->y;
	L.z = l1->lightDir->z - p->z;

	// normalize L
	GLfloat L_size = sqrt((double)L.x * L.x + (double)L.y * L.y + (double)L.z * L.z);
	L.x = L.x / L_size;
	L.y = L.y / L_size;
	L.z = L.z / L_size;

	GLfloat NdotL = (double)n->x * L.x + (double)n->y * L.y + (double)n->z * L.z;
	if (NdotL <= 0) {
		NdotL = 0;
	}

	vector R; // R = 2(N.L)N - L
	R.x = 2 * NdotL * n->x - L.x;
	R.y = 2 * NdotL * n->y - L.y;
	R.z = 2 * NdotL * n->z - L.z;

	// normalize R
	GLfloat R_size = sqrt((double)R.x * R.x + (double)R.y * R.y + (double)R.z * R.z);
	R.x = R.x / R_size;
	R.y = R.y / R_size;
	R.z = R.z / R_size;

	vector V;
	V.x = 0.0f - p->x;
	V.y = 0.0f - p->y;
	V.z = 0.0f - p->z;

	// normalize V
	GLfloat V_size = sqrt((double)V.x * V.x + (double)V.y * V.y + (double)V.z * V.z);
	V.x = V.x / V_size;
	V.y = V.y / V_size;
	V.z = V.z / V_size;

	GLfloat VdotR = (double)V.x * R.x + (double)V.y * R.y + (double)V.z * R.z;
	if(VdotR < 0 || NdotL<=0) {
		VdotR = 0;
	}

	/* so far, just finds ambient component of color */
	         // ambient        // diffuse                       // specular
	//c->r = (m->amb + NdotL * l1->diff->r * l1->i->r + pow(VdotR, l1->spec->shininess) * l1->spec->r * l1->i->r) * m->c.r;
	//c->g = (m->amb + NdotL * l1->diff->g * l1->i->g + pow(VdotR, l1->spec->shininess) * l1->spec->g * l1->i->g) * m->c.g;
	//c->b = (m->amb + NdotL * l1->diff->b * l1->i->b + pow(VdotR, l1->spec->shininess) * l1->spec->b * l1->i->b) * m->c.b;

	       // ambient        // diffuse                       // specular
	c->r = m->amb * m->c.r + NdotL * l1->diff->r * l1->i->r + pow(VdotR, l1->spec->shininess) * l1->spec->r * l1->i->r;
	c->g = m->amb * m->c.g + NdotL * l1->diff->g * l1->i->g + pow(VdotR, l1->spec->shininess) * l1->spec->g * l1->i->g;
	c->b = m->amb * m->c.b + NdotL * l1->diff->b * l1->i->b + pow(VdotR, l1->spec->shininess) * l1->spec->b * l1->i->b;

	/* clamp color values to 1.0 */
	if (c->r > 1.0) c->r = 1.0;
	if (c->g > 1.0) c->g = 1.0;
	if (c->b > 1.0) c->b = 1.0;

}
