#include <iostream>
#include "Angel.h"
#include <vector>
#include <Math.h>

using namespace Angel;
using namespace std;
typedef vec4 point4;
typedef vec4 color4;
const GLint width = 500;
const GLint height = 500;
vector<point4> sphere;
vector<point4> normal;


const double PI = 3.141592653589793238463;

const int meridians = 100;
const int parallels = 100;


point4 light_position(2.0, 3.0, 2.0, 1.0); //wrt camera
color4 light_ambient(0.2, 0.2, 0.2, 1.0);
color4 light_diffuse(1.0, 1.0, 1.0, 1.0);
color4 light_specular(1.0, 1.0, 1.0, 1.0);

vector<point4> ambient_products;
vector<point4> diffuse_products;
vector<point4> specular_products;

GLint ModelView, Projection;





void fillSpherePoints() {
	/*
	float parallelStep = 2 * PI / parallels;
	float meridianStep = PI / meridians;

	float parallelAngle, meridianAngle;
	for (int i = 0; i <= meridians; ++i)
	{
		float radius = 1.0;
		meridianAngle = PI / 2 - i * meridianStep;
		float xy = radius * cosf(meridianAngle);
		float z = radius * sinf(meridianAngle);


		for (int j = 0; j <= parallels; ++j)
		{
			parallelAngle = j * parallelStep;


			float x = xy * cosf(parallelAngle);
			float y = xy * sinf(parallelAngle);

			point4 point = { x,y,z,1.0 };
			vec3 normalized = normalize(vec3(x, y, z));
			normal.push_back(vec4(normalized, 0.0));
			ambient_products.push_back(light_ambient*vec4(1.0, 0.0, 0.0, 1.0));
			diffuse_products.push_back(light_diffuse*vec4(1.0, 0.61424, 0.07568, 1.0));
			specular_products.push_back(light_specular*vec4(0.0215, 0.1745, 0.0215, 1.0));
			sphere.push_back(point);
		}
	}
	*/


}

void fillTorus1() {
	float innerRadius = 0.1;
	float outerRadius = 0.78;

	float innerAngle;
	float outerAngle;

	float s, t, x, y, z, twopi;
	int numberOfOuter = 100;
	int numberOfInner = 100;

	for (int i = 0; i < numberOfOuter; i++) {
		for (int j = 0; j <= numberOfInner; j++) {
			for (int k = 1; k >= 0; k--) {
				outerAngle = (i + k) % numberOfOuter + 0.5;
				innerAngle = j % numberOfInner;

				outerAngle *= 2 * PI;
				innerAngle *= 2 * PI;

				x = (outerRadius + innerRadius * cos(outerAngle / numberOfOuter))*cos(innerAngle / numberOfInner);
				y = (outerRadius + innerRadius * cos(outerAngle / numberOfOuter))*sin(innerAngle / numberOfInner);
				z = innerRadius * sin(outerAngle / numberOfOuter);

				// tangents for outer
				float tx = -sin(innerAngle / numberOfInner);
				float ty = cos(innerAngle / numberOfInner);
				float tz = 0;
				// tangents for inner
				float sx = cos(innerAngle / numberOfOuter)*(-sin(outerAngle / numberOfOuter));
				float sy = sin(innerAngle / numberOfOuter)*(-sin(outerAngle / numberOfOuter));
				float sz = cos(outerAngle / numberOfOuter);				vec3 norm = cross(vec3(tx, ty, tz), vec3(sx, sy, sz));
				point4 point = { x,y,z,1.0 };
				vec3 normalized = normalize(norm);
				normal.push_back(vec4(normalized, 0.0));
				ambient_products.push_back(light_ambient*vec4(1.0, 0.0, 0.0, 1.0));
				diffuse_products.push_back(light_diffuse*vec4(1.0, 0.61424, 0.07568, 1.0));
				specular_products.push_back(light_specular*vec4(0.0215, 0.1745, 0.0215, 1.0));
				sphere.push_back(point);
			}
		}

	}
}
void pushColor() {
	ambient_products.push_back(light_ambient*vec4(1.0, 0.0, 0.0, 1.0));
	diffuse_products.push_back(light_diffuse*vec4(0.0, 0.61424, 0.07568, 1.0));
	specular_products.push_back(light_specular*vec4(0.0215, 0.1745, 0.0215, 1.0));
}
void fillTorus2() {
	float innerRadius = 0.1;
	float outerRadius = 1.0;

	float innerAngle;
	float outerAngle;

	float s, t, x, y, z, twopi;
	int numberOfOuter = 100;
	int numberOfInner = 100;

	for (int i = 0; i < numberOfOuter; i++) {
		for (int j = 0; j <= numberOfInner; j++) {
			for (int k = 1; k >= 0; k--) {
				outerAngle = (i + k) % numberOfOuter + 0.5;
				innerAngle = j % numberOfInner;

				outerAngle *= 2 * PI;
				innerAngle *= 2 * PI;

				x = (outerRadius + innerRadius * cos(outerAngle / numberOfOuter))*cos(innerAngle / numberOfInner);
				y = (outerRadius + innerRadius * cos(outerAngle / numberOfOuter))*sin(innerAngle / numberOfInner);
				z = innerRadius * sin(outerAngle / numberOfOuter);

				// tangents for outer
				float tx = -sin(innerAngle / numberOfInner);
				float ty = cos(innerAngle / numberOfInner);
				float tz = 0;
				// tangents for inner
				float sx = cos(innerAngle / numberOfOuter)*(-sin(outerAngle / numberOfOuter));
				float sy = sin(innerAngle / numberOfOuter)*(-sin(outerAngle / numberOfOuter));
				float sz = cos(outerAngle / numberOfOuter);				mat4 rY = mat4(cos(90 * PI / 180), 0.0, sin(90 * PI / 180), 0.0,
					0.0, 1.0, 0.0, 0.0,
					-sin(90 * PI / 180), 0.0, cos(90 * PI / 180), 0.0,
					0.0, 0.0, 0.0, 1.0);				vec4 norm = rY * vec4(cross(vec3(tx, ty, tz), vec3(sx, sy, sz)), 0.0);
				point4 point = rY * point4(x, y, z, 1.0);
				vec4 normalized = normalize(norm);
				normal.push_back(normalized);
				ambient_products.push_back(light_ambient*vec4(1.0, 0.0, 0.0, 1.0));
				diffuse_products.push_back(light_diffuse*vec4(1.0, 0.61424, 0.07568, 1.0));
				specular_products.push_back(light_specular*vec4(0.0215, 0.1745, 0.0215, 1.0));
				sphere.push_back(point);
			}
		}
	}
}

void triangle(const point4 &a, const point4 &b, const point4 &c) {
	sphere.push_back(a);
	pushColor();
	vec4 norm = normalize(cross(b - a, c - a));
	norm.w = 0.0;
	normal.push_back(norm);
	sphere.push_back(b);
	norm = normalize(cross(a - c, b - c));
	norm.w = 0.0;
	normal.push_back(norm);
	pushColor();
	sphere.push_back(c);
	norm = normalize(cross(a - b, c - b));
	norm.w = 0.0;
	normal.push_back(norm);
	pushColor();
}

void fillTetraHedron() {
	triangle(point4(-0.1, 0.0, 1.2, 1.0), point4(0.1, 0.0, 1.7, 1.0), point4(0.2, 0.0, 1.2, 1.0));
	triangle(point4(0.1, 0.0, 1.2, 1.0), point4(0.0, 0.5 / 3, 1.5, 1.0), point4(0.0, 0.0, 1.7, 1.0));
	triangle(point4(0.0, 0.5 / 3, 1.5, 1.0), point4(-0.1, 0.0, 1.2, 1.0), point4(0.0, 0.0, 1.7, 1.0));
	triangle(point4(0.0, 0.5 / 3, 1.5, 1.0), point4(-0.1, 0.0, 1.2, 1.0), point4(0.2, 0.0, 1.2, 1.0));
}
void init() {

	//	fillSpherePoints();
//	fillTorus1();
	
	fillTorus2();
	fillTetraHedron();

	// Create a vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create and initialize a buffer object
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	glBufferData(GL_ARRAY_BUFFER, sizeof(point4)*sphere.size() + sizeof(point4)*normal.size() + sizeof(point4)*ambient_products.size()
		+ sizeof(point4)*diffuse_products.size() + sizeof(point4)*specular_products.size(), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(point4)*sphere.size(), sphere.data());
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(point4)*sphere.size(), sizeof(point4)*normal.size(), normal.data());
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(point4)*sphere.size() + sizeof(point4)*normal.size(), sizeof(point4)*ambient_products.size(), ambient_products.data());
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(point4)*sphere.size() + sizeof(point4)*normal.size() + sizeof(point4)*ambient_products.size()
		, sizeof(point4)*diffuse_products.size(), diffuse_products.data());
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(point4)*sphere.size() + sizeof(point4)*normal.size() + sizeof(point4)*ambient_products.size()
		+ sizeof(point4)*diffuse_products.size(), sizeof(point4)*specular_products.size(), specular_products.data());

	// Load shaders and use the resulting shader program
	GLuint program = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(program);

	// set up vertex arrays
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));

	GLuint vNormal = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(point4)*sphere.size()));

	GLuint AmbientProduct = glGetAttribLocation(program, "AmbientProduct");
	glEnableVertexAttribArray(AmbientProduct);
	glVertexAttribPointer(AmbientProduct, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(point4)*sphere.size() + sizeof(point4)*normal.size()));

	GLuint DiffuseProduct = glGetAttribLocation(program, "DiffuseProduct");
	glEnableVertexAttribArray(DiffuseProduct);
	glVertexAttribPointer(DiffuseProduct, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(point4)*sphere.size() + sizeof(point4)*normal.size() + sizeof(point4)*ambient_products.size()));

	GLuint SpecularProduct = glGetAttribLocation(program, "SpecularProduct");
	glEnableVertexAttribArray(SpecularProduct);
	glVertexAttribPointer(SpecularProduct, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(point4)*sphere.size() + sizeof(point4)*normal.size() + sizeof(point4)*ambient_products.size() + sizeof(point4)*diffuse_products.size()));

	float material_shininess = 960.8;
	glUniform1f(glGetUniformLocation(program, "Shininess"), material_shininess);
	glUniform4fv(glGetUniformLocation(program, "LightPosition"), 1, light_position);

	ModelView = glGetUniformLocation(program, "ModelView");
	Projection = glGetUniformLocation(program, "Projection");

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	point4 at(0.0, 0.0, 0.0, 1.0);
	point4 eye(0.0, 0.0, 3.0, 1.0);
	vec4 up(0.0, 1.0, 0.0, 0.0);

	mat4 model_view = LookAt(eye, at, up);
	glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_view);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, sphere.size());
	glutSwapBuffers();
}
void myReshape(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h);
	GLfloat aspect = GLfloat(w) / h;
	mat4 projection = Perspective(60.0, aspect, 0.5, 20.0);
	glUniformMatrix4fv(Projection, 1, GL_TRUE, projection);
}
int main(int argc, char **argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Sphere");
	glewExperimental = GL_TRUE;
	glewInit();
	init();
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutMainLoop();
	return 0;
}