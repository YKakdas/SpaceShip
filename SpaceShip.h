#ifndef  SPACESHIP_H
#define SPACESHIP_H

#include <iostream>
#include "Angel.h"
#include <vector>
#include <Math.h>
#include <string>
#include <playsoundapi.h>


using namespace Angel;
using namespace std;

typedef vec4 point4;
typedef vec4 color4;

const GLint width = 1920;
const GLint height = 1080;

vector<point4> points;
vector<point4> normal;


enum modes { ModeC, ModeS, ModeT, ModeW };

string viewModeArr[] = { "ModeC","ModeS","ModeT","ModeW" };

modes viewMode = ModeC;

const double PI = 3.141592653589793238463;

const int meridians = 100;
const int parallels = 100;


point4 light_position(2.0, 3.0, 300.0, 1.0); //wrt camera
color4 light_ambient(0.2, 0.2, 0.2, 1.0);
color4 light_diffuse(1.0, 1.0, 1.0, 1.0);
color4 light_specular(1.0, 1.0, 1.0, 1.0);


vector<point4> ambient_products;
vector<point4> diffuse_products;
vector<point4> specular_products;

GLint numVerticesOfPlanet;
GLint numVerticesOfTorus;
GLint numVerticesOfTetrahedron = 12;
GLint numVerticesOfCircle = 100;

GLint radiusShip = 1.0;

GLint ModelView, Projection;

GLint translatePos;
GLint thetaPos;

vec4 translate;
vec4 translateShip = vec4(105.0, 15.0, 0.0, 1.0);
vec3 Theta = { 0.0,0.0,0.0 };

GLfloat angle = 0;

point4 at(105.0, 15.0, -3.0, 1.0);
point4 eye(105.0, 15.0, -0.8, 1.0);
vec4 up(0.0, 1.0, 0.0, 0.0);

vec4 direction(0.0, 0.0, -1.0, 0.0);

GLfloat moveSpeed = 2.0;
GLfloat rotationSpeed = 0.0;

bool isOneStep = false;
bool isPaused = false;

int planetCount = 0;

vec4 planet_coords[8] = { {30, 30, -30,1},
{30, 15,-170,1},
{80, 25,-110,1},
{70, 12,-60,1},
{90, 13,-150,1},
{120, 17,-80,1},
{150, 15, -40,1},
{160, 22, -170,1} };

vec4 spaceshipCoord = vec4(105.0, 15.0, 0.0, 1.0);

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
{1.00, 1.00, 1.00,1.0} };

vec4 specular_colors[8] = { {0.30, 0.30, 0.30,1.0},
{1.00, 0.00, 0.00,1.0},
{0.00, 1.00, 0.00,1.0},
{0.00, 0.00, 1.00,1.0},
{1.00, 1.00, 0.00,1.0},
{1.00, 0.00, 1.00,1.0},
{0.00, 1.00, 1.00,1.0},
{1.00, 1.00, 1.00,1.0} };

// Function Prototypes

void playSound();
void stopSound();
void triangle(const point4 &a, const point4 &b, const point4 &c);
int fillPlanetPoints(int radius, const vec4 &ambientColor, const vec4 &diffuseColor, const vec4 &specular);
void fillTorus1();
void fillTorus2();
void pushColor();
void fillTetraHedron();
void init();
void myDisplay(void);
void moveSpaceship(int id);
void rotateStation(int id);
void myKeyboard(unsigned char key, int x, int y);
void outputDebugInfo();
void myMouse(int btn, int state, int x, int y);
void mySpecialKeyboard(int key, int x, int y);
void myReshape(GLsizei w, GLsizei h);
#endif // ! SPACESHIP_H

