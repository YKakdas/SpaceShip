#include "SpaceShip.h"




void playSound() {
	PlaySound(TEXT("starwars.wav"), NULL, SND_LOOP | SND_ASYNC);
}

void stopSound() {
	PlaySound(NULL, NULL, SND_LOOP | SND_ASYNC);
}
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
	planetCount++;

	if (planetCount < 9) {
		for (int i = 0; i < numVerticesOfCircle; i++) {
			float angle = 2 * PI*i / numVerticesOfCircle;
			float x = cos(angle)*(radius + 2.0);
			float y = sin(angle)*(radius + 2.0);
			float z = 0.0;
			vec4 color = { 1.0,1.0,1.0,1.0 };
			points.push_back(vec4(x, y, z, 1.0));
			vec3 normalized = normalize(vec3(x, y, z));
			normal.push_back(vec4(normalized, 0.0));
			ambient_products.push_back(light_ambient*color);
			diffuse_products.push_back(light_diffuse*color);
			specular_products.push_back(light_specular*color);
		}
		for (int i = 0; i < numVerticesOfCircle; i++) {
			float angle = 2 * PI*i / numVerticesOfCircle;
			float x = cos(angle)*(radius + 2.0);
			float y = sin(angle)*(radius + 2.0);
			float z = 0.0;
			vec4 color = { 1.0,1.0,1.0,1.0 };
			points.push_back(vec4(x, y, z, 1.0));
			vec3 normalized = normalize(vec3(x, y, z));
			normal.push_back(vec4(normalized, 0.0));
			ambient_products.push_back(light_ambient*color);
			diffuse_products.push_back(light_diffuse*color);
			specular_products.push_back(light_specular*color);
		}
	}

	if (planetCount == 9) { // station is drawn
		mat4 rY = mat4(cos(90 * PI / 180), 0.0, sin(90 * PI / 180), 0.0,
			0.0, 1.0, 0.0, 0.0,
			-sin(90 * PI / 180), 0.0, cos(90 * PI / 180), 0.0,
			0.0, 0.0, 0.0, 1.0);

		vec4 point1 = rY * vec4{ -0.5,0.5,-4.0,1.0 };
		vec4 point2 = rY * vec4{ -0.5,-0.5,-4.0,1.0 };
		vec4 point3 = rY * vec4{ 0.5,-0.5,-4.0,1.0 };
		vec4 point4 = rY * vec4{ 0.5,0.5,-4.0,1.0 };

		triangle(point1, point2, point3);
		triangle(point3, point4, point1);
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
	triangle(point4(-0.1, 0.0, -3.2, 1.0), point4(0.0, 0.0, -2.7, 1.0), point4(0.1, 0.0, -3.2, 1.0));
	triangle(point4(0.1, 0.0, -3.2, 1.0), point4(0.0, 0.2, -2.9, 1.0), point4(0.0, 0.0, -2.7, 1.0));
	triangle(point4(0.0, 0.2, -2.9, 1.0), point4(-0.1, 0.0, -3.2, 1.0), point4(0.0, 0.0, -3.7, 1.0));
	triangle(point4(0.0, 0.2, -2.9, 1.0), point4(-0.1, 0.0, -3.2, 1.0), point4(0.1, 0.0, -3.2, 1.0));
}
void init() {

	for (int i = 0; i < 8; i++) {
		numVerticesOfPlanet = fillPlanetPoints(3, ambient_colors[i], diffuse_colors[i], specular_colors[i]);
	}
	fillPlanetPoints(4, stationAmbient, stationDiffuse, stationSpecular);
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
		glUniform3fv(thetaPos, 1, vec3(0.0, 0.0, 0.0));
		glDrawArrays(GL_TRIANGLE_FAN, numVerticesOfPlanet*i + numVerticesOfCircle * i * 2, numVerticesOfPlanet);
		glUniform3fv(thetaPos, 1, vec3(0.0, 0.0, 45.0));
		glDrawArrays(GL_LINE_LOOP, numVerticesOfPlanet*(i + 1) + numVerticesOfCircle * i * 2, numVerticesOfCircle);
		glUniform3fv(thetaPos, 1, vec3(90.0, 0.0, 45.0));
		glDrawArrays(GL_LINE_LOOP, numVerticesOfPlanet*(i + 1) + numVerticesOfCircle * (1 + 2 * i), numVerticesOfCircle);
	}

	translate = stationCoord;
	glUniform3fv(thetaPos, 1, Theta);
	glUniform4fv(translatePos, 1, translate);
	glDrawArrays(GL_TRIANGLE_FAN, numVerticesOfPlanet * 8 + numVerticesOfCircle * 16, numVerticesOfPlanet);
	glDrawArrays(GL_TRIANGLES, numVerticesOfPlanet * 9 + numVerticesOfCircle * 16, 6);


	glUniform3fv(thetaPos, 1, vec3(0.0, angle, 0.0));

	for (int i = 0; i < 2; i++) {
		glUniform4fv(translatePos, 1, translateShip);
		glDrawArrays(GL_TRIANGLE_STRIP, numVerticesOfPlanet * 9 + numVerticesOfTorus * i + 6 + numVerticesOfCircle * 16, numVerticesOfTorus);
	}

	glUniform3fv(thetaPos, 1, vec3(0.0, 0.0, angle));
	glUniform4fv(translatePos, 1, spaceshipCoord);
	glDrawArrays(GL_TRIANGLES, numVerticesOfPlanet * 9 + numVerticesOfTorus * 2 + 6 + numVerticesOfCircle * 16, numVerticesOfTetrahedron);

	glutSwapBuffers();
}

void moveSpaceship(int id) {
	if (isPaused) return;
	spaceshipCoord += direction * moveSpeed;
	translateShip += direction * moveSpeed;
	if (viewMode == ModeC || viewMode == ModeT) {
		eye += direction * moveSpeed;
		at += direction * moveSpeed;
	}

	glutPostRedisplay();
	glutTimerFunc(500, moveSpaceship, 0);
}

void rotateStation(int id) {
	if (isPaused) return;
	Theta.y += rotationSpeed;
	if (viewMode == ModeS) {

		mat4 rY = mat4(cos(Theta.y * PI / 180), 0.0, sin(Theta.y * PI / 180), 0.0,
			0.0, 1.0, 0.0, 0.0,
			-sin(Theta.y * PI / 180), 0.0, cos(Theta.y * PI / 180), 0.0,
			0.0, 0.0, 0.0, 1.0);

		eye = rY * vec4{ 0.0,0.0,-4.0,1.0 } +stationCoord;
		at = rY * vec4(0.0, 0.0, -5.0, 1.0) + stationCoord;
	}

	glutTimerFunc(50, rotateStation, 0);
	glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y) {
	if (key == 'p' || key == 'P') {
		isPaused = !isPaused;
		if (isPaused) {
			stopSound();
			return;
		}
		else {
			playSound();
			glutTimerFunc(0, moveSpaceship, 0);
			glutTimerFunc(0, rotateStation, 0);
		}
	}

	if (isPaused && !isOneStep) return;
	if (viewMode != ModeS) {
		if (key == 'a' || key == 'A') {
			moveSpeed -= 0.5;
			if (moveSpeed < 0.0) {
				moveSpeed = 0.0;
			}
		}
		if (key == 'd' || key == 'D') {
			moveSpeed += 0.5;
		}
	}

	if (key == 'c' || key == 'C') {
		viewMode = ModeC;
		eye.x = spaceshipCoord.x;
		eye.y = spaceshipCoord.y;
		eye.z = spaceshipCoord.z - 2;
		at.x = eye.x;
		at.y = eye.y;
		at.z = eye.z - 1;
		glutPostRedisplay();
	}
	else if (key == 's' || key == 'S') {
		viewMode = ModeS;
		eye = stationCoord;
		at = eye;
		at.z -= 2;
		glutPostRedisplay();
	}
	else if (key == 't' || key == 'T') {
		viewMode = ModeT;
		eye.x = spaceshipCoord.x;
		eye.y = spaceshipCoord.y + 2.0;
		eye.z = spaceshipCoord.z + 4;
		at.x = eye.x;
		at.y = eye.y;
		at.z = eye.z - 2;
		glutPostRedisplay();
	}
	else if (key == 'w' || key == 'W') {
		viewMode = ModeW;
		eye = vec4(105.0, 200.0, -1.0, 1.0);
		at = vec4(105.0, 15.0, -3.0, 1.0);
		glutPostRedisplay();
	}
	else if (key == 'j' || key == 'J') {
		rotationSpeed += 2.0;
	}
	else if (key == 'k' || key == 'K') {
		rotationSpeed -= 2.0;
		if (rotationSpeed < 0) rotationSpeed = 0.0;
	}
}

void myMouse(int btn, int state, int x, int y) {
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		outputDebugInfo();
		if (!isPaused) { // if game is not paused,first pause it
			isPaused = !isPaused;
			stopSound();
		}
		else { // if game is paused
			isPaused = false;
			isOneStep = true;
			playSound();
			moveSpaceship(0);
			rotateStation(0);
			stopSound();
			isPaused = true;
		}
	}
}

void mySpecialKeyboard(int key, int x, int y) {
	if (isPaused && !isOneStep) return;
	if (angle == 360 || angle == -360) {
		angle = 0.0;
	}
	if (viewMode != ModeS) {
		if (key == GLUT_KEY_LEFT) {
			angle += 5;
			direction.x = -1.0*sin(angle*PI / 180)*moveSpeed;
			direction.z = -1.0*cos(angle*PI / 180)*moveSpeed;
		}
		else if (key == GLUT_KEY_RIGHT) {
			angle -= 5;
			direction.x = -1.0*sin(angle*PI / 180)*moveSpeed;
			direction.z = -1.0*cos(angle*PI / 180)*moveSpeed;
		}
	}
}

void outputDebugInfo() {
	vec4 normalizedDirection = normalize(direction);
	cout << "\x1B[2J\x1B[H";
	cout << "View Mode is : " << viewModeArr[viewMode] << "\n";
	cout << "Spaceship coordinates : (" << spaceshipCoord.x << "," << spaceshipCoord.y << "," << spaceshipCoord.z << ")\n";
	cout << "Spaceship direction : (" << normalizedDirection.x << "," << normalizedDirection.y << "," << normalizedDirection.z << ")\n";
	cout << "Spaceship velocity : " << moveSpeed << "\n";
	cout << "----------------------------------------------------------------->\n";
	cout << "Station coordinates : (" << stationCoord.x << "," << stationCoord.y << "," << stationCoord.z << ")\n";
	cout << "Spaceship rotation angel : " << angle << "\n";
	cout << "----------------------------------------------------------------->";
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
	glutCreateWindow("3D Space Simulation");
	glewExperimental = GL_TRUE;
	glewInit();
	init();
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeyboard);
	glutMouseFunc(myMouse);
	glutTimerFunc(1000, moveSpaceship, 0);
	glutTimerFunc(1000, rotateStation, 0);
	playSound();
	glutMainLoop();
	return 0;
}