#include <iostream>
#include "Angel.h"
#include <vector>
#include <Math.h>

using namespace Angel;
using namespace std;
typedef vec4 point4;
typedef vec4 color4;
const GLint width = 1920;
const GLint height = 1080;
vector<point4> points;
vector<point4> normal;


const double PI = 3.141592653589793238463;

const int meridians = 100;
const int parallels = 100;


point4 light_position(2.0, 3.0, 1200.0, 1.0); //wrt camera
color4 light_ambient(0.2, 0.2, 0.2, 1.0);
color4 light_diffuse(1.0, 1.0, 1.0, 1.0);
color4 light_specular(1.0, 1.0, 1.0, 1.0);


vector<point4> ambient_products;
vector<point4> diffuse_products;
vector<point4> specular_products;

GLint numVerticesOfPlanet;
GLint numVerticesOfTorus;
GLint numVerticesOfTetrahedron = 12;

GLint radiusShip = 3.0;

GLint ModelView, Projection;

GLint translatePos;
vec4 translate;
vec4 translateShip = vec4(105.0, 15.0, 0.0, 1.0);
GLint thetaPos;
vec3 Theta;

point4 at(105.0, 15.0, -3.0, 1.0);
point4 eye(105.0, 15.0, -0.8, 1.0);
vec4 up(0.0, 1.0, 0.0, 0.0);

vec4 direction(0.0, 0.0, -1.0, 0.0);
vec4 movedAway = (0.0, 0.0, 0.0, 1.0);
bool isEyeMove = true;

vec4 planet_coords[8] = { {30, 30, -30,1},
{30, 15,-170,1},
{80, 25,-110,1},
{70, 12,-60,1},
{90, 13,-150,1},
{120, 17,-80,1},
{150, 15, -40,1},
{160, 22, -170,1} };

vec4 stationCoord = vec4(100.0, 10.0, -10.0, 1.0);
vec4 stationAmbient = vec4(0.5, 0.5, 0.5, 1.0);
vec4 stationDiffuse = vec4(0.5, 0.5, 0.5, 1.0);
vec4 stationSpecular = vec4(0.5, 0.5, 0.5, 1.0);


/*colors(rgb) for each planet */
vec4 ambient_colors[8] = { {0.30, 0.30, 0.30,1.0},
{1.00, 0.00, 0.00,1.0},
{0.00, 1.00, 0.00,1.0},
{0.00, 0.00, 1.00,1.0},
{1.00, 1.00, 0.00,1.0},
{1.00, 0.00, 1.00,1.0},
{0.00, 1.00, 1.00,1.0},
{1.00, 1.00, 1.00,1.0} };

vec4 diffuse_colors[8] = { {0.30, 0.30, 0.30,1.0},
{1.00, 0.00, 0.00,1.0},
{0.00, 1.00, 0.00,1.0},
{0.00, 0.00, 1.00,1.0},
{1.00, 1.00, 0.00,1.0},
{1.00, 0.00, 1.00,1.0},
{0.00, 1.00, 1.00,1.0},
{1.00, 1.00, 1.00,1.0} };vec4 specular_colors[8] = { {0.30, 0.30, 0.30,1.0},
{1.00, 0.00, 0.00,1.0},
{0.00, 1.00, 0.00,1.0},
{0.00, 0.00, 1.00,1.0},
{1.00, 1.00, 0.00,1.0},
{1.00, 0.00, 1.00,1.0},
{0.00, 1.00, 1.00,1.0},
{1.00, 1.00, 1.00,1.0} };

int fillPlanetPoints(int radius, const vec4 &ambientColor, const vec4 &diffuseColor, const vec4 &specular) {
	int numVertices = 0;
	float parallelStep = 2 * PI / parallels;
	float meridianStep = PI / meridians;

	float parallelAngle, meridianAngle;
	for (int i = 0; i <= meridians; ++i)
	{
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
			ambient_products.push_back(light_ambient*ambientColor);
			diffuse_products.push_back(light_diffuse*diffuseColor);
			specular_products.push_back(light_specular*specular);
			points.push_back(point);
			numVertices++;
		}
	}
	return numVertices;
}

void fillTorus1() {
	int numVertices = 0;
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
				float sz = cos(outerAngle / numberOfOuter);

				vec3 norm = cross(vec3(tx, ty, tz), vec3(sx, sy, sz));

				point4 point = { x,y,z,1.0 };
				vec3 normalized = normalize(norm);
				normal.push_back(vec4(normalized, 0.0));
				ambient_products.push_back(light_ambient*vec4(1.0, 0.0, 0.0, 1.0));
				diffuse_products.push_back(light_diffuse*vec4(1.0, 0.61424, 0.07568, 1.0));
				specular_products.push_back(light_specular*vec4(0.0215, 0.1745, 0.0215, 1.0));
				points.push_back(point);
				numVertices++;
			}
		}
	}
	numVerticesOfTorus = numVertices;
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
				float sz = cos(outerAngle / numberOfOuter);

				mat4 rY = mat4(cos(90 * PI / 180), 0.0, sin(90 * PI / 180), 0.0,
					0.0, 1.0, 0.0, 0.0,
					-sin(90 * PI / 180), 0.0, cos(90 * PI / 180), 0.0,
					0.0, 0.0, 0.0, 1.0);

				vec4 norm = rY * vec4(cross(vec3(tx, ty, tz), vec3(sx, sy, sz)), 0.0);

				point4 point = rY * point4(x, y, z, 1.0);
				vec4 normalized = normalize(norm);
				normal.push_back(normalized);
				ambient_products.push_back(light_ambient*vec4(1.0, 0.0, 0.0, 1.0));
				diffuse_products.push_back(light_diffuse*vec4(1.0, 0.61424, 0.07568, 1.0));
				specular_products.push_back(light_specular*vec4(0.0215, 0.1745, 0.0215, 1.0));
				points.push_back(point);
			}
		}
	}
}

void triangle(const point4 &a, const point4 &b, const point4 &c) {
	points.push_back(a);
	pushColor();
	vec4 norm = normalize(cross(b - a, c - a));
	norm.w = 0.0;
	normal.push_back(norm);
	points.push_back(b);
	norm = normalize(cross(a - c, b - c));
	norm.w = 0.0;
	normal.push_back(norm);
	pushColor();
	points.push_back(c);
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

	for (int i = 0; i < 8; i++) {
		numVerticesOfPlanet = fillPlanetPoints(2, ambient_colors[i], diffuse_colors[i], specular_colors[i]);
	}
	fillPlanetPoints(3, stationAmbient, stationDiffuse, stationSpecular);
	fillTorus1();
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

	glBufferData(GL_ARRAY_BUFFER, sizeof(point4)*points.size() + sizeof(point4)*normal.size() + sizeof(point4)*ambient_products.size()
		+ sizeof(point4)*diffuse_products.size() + sizeof(point4)*specular_products.size(), NULL, GL_STATIC_DRAW);

	int offset = sizeof(point4)*points.size();
	glBufferSubData(GL_ARRAY_BUFFER, 0, offset, points.data());
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(point4)*normal.size(), normal.data());
	offset += sizeof(point4)*normal.size();
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(point4)*ambient_products.size(), ambient_products.data());
	offset += sizeof(point4)*ambient_products.size();
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(point4)*diffuse_products.size(), diffuse_products.data());
	offset += sizeof(point4)*diffuse_products.size();
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(point4)*specular_products.size(), specular_products.data());

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
		BUFFER_OFFSET(sizeof(point4)*points.size()));

	GLuint AmbientProduct = glGetAttribLocation(program, "AmbientProduct");
	glEnableVertexAttribArray(AmbientProduct);
	glVertexAttribPointer(AmbientProduct, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(point4)*points.size() + sizeof(point4)*normal.size()));

	GLuint DiffuseProduct = glGetAttribLocation(program, "DiffuseProduct");
	glEnableVertexAttribArray(DiffuseProduct);
	glVertexAttribPointer(DiffuseProduct, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(point4)*points.size() + sizeof(point4)*normal.size() + sizeof(point4)*ambient_products.size()));

	GLuint SpecularProduct = glGetAttribLocation(program, "SpecularProduct");
	glEnableVertexAttribArray(SpecularProduct);
	glVertexAttribPointer(SpecularProduct, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(point4)*points.size() + sizeof(point4)*normal.size() + sizeof(point4)*ambient_products.size() + sizeof(point4)*diffuse_products.size()));

	float material_shininess = 960.8;
	glUniform1f(glGetUniformLocation(program, "Shininess"), material_shininess);
	glUniform4fv(glGetUniformLocation(program, "LightPosition"), 1, light_position);
	translatePos = glGetUniformLocation(program, "TranslateVec");
	thetaPos = glGetUniformLocation(program, "theta");

	ModelView = glGetUniformLocation(program, "ModelView");
	Projection = glGetUniformLocation(program, "Projection");

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	mat4 model_view = LookAt(eye, at, up);
	glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_view);


	for (int i = 0; i < 8; i++) {
		translate = planet_coords[i];
		glUniform4fv(translatePos, 1, translate);
		glDrawArrays(GL_TRIANGLE_FAN, numVerticesOfPlanet*i, numVerticesOfPlanet);
	}

	translate = stationCoord;
	glUniform4fv(translatePos, 1, translate);
	glDrawArrays(GL_TRIANGLE_FAN, numVerticesOfPlanet * 8, numVerticesOfPlanet);

	for (int i = 0; i < 2; i++) {
		glUniform4fv(translatePos, 1, translateShip);
		glDrawArrays(GL_TRIANGLE_STRIP, numVerticesOfPlanet * 9 + numVerticesOfTorus * i, numVerticesOfTorus);
	}

	//	translate = vec4(105.0, 15.0, -2.8, 1.0);
	//	glUniform4fv(translatePos, 1, translate);
	//	glDrawArrays(GL_TRIANGLE_STRIP, numVerticesOfPlanet * 8 + numVerticesOfTorus * 2, numVerticesOfTetrahedron);

	glutSwapBuffers();
}

void myKeyboard(unsigned char key, int x, int y) {
	if (key == 'c') {
		isEyeMove = true;
		eye.x = 105.0;
		eye.y = 15.0;
		eye.z = movedAway.z - radiusShip;
		at.z = eye.z - 2;
		glutPostRedisplay();
	}
	else if (key == 's') {
		isEyeMove = false;
		eye = vec4(100.0, 10.0, -13.0, 1.0);
		at = vec4(100.0, 10.0, -15.0, 1.0);
		glutPostRedisplay();
	}
	else if (key == 't') {
		isEyeMove = true;
		eye.x = 105.0;
		eye.y = 15.0;
		at.x = eye.x;
		at.y = eye.y;
		eye.z = movedAway.z + radiusShip;
		at.z = eye.z - 2;
		glutPostRedisplay();
	}
	else if (key == 'w') {
		isEyeMove = false;
		eye = vec4(105.0, 15.0, 20.0, 1.0);
		at = vec4(105.0, 15.0, -3.0, 1.0);
		glutPostRedisplay();
	}
}
void myTimer(int id) {
	translateShip += direction;
	if (isEyeMove) {
		eye += direction;
		at += direction;
	}
	movedAway += direction;

	glutPostRedisplay();
	glutTimerFunc(1000, myTimer, 0);
}
void myReshape(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h);
	GLfloat aspect = GLfloat(w) / h;
	mat4 projection = Perspective(90.0, aspect, 0.5, 20000.0);
	glUniformMatrix4fv(Projection, 1, GL_TRUE, projection);
}
int main(int argc, char **argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Sphere");
	glewExperimental = GL_TRUE;
	glewInit();
	init();
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(myKeyboard);
	glutTimerFunc(1000, myTimer, 0);
	glutMainLoop();
	return 0;
}