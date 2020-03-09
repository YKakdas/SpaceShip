## 3D Space Simulation

Aim of the game is moving space ship through planets and station and look the space from different views.

#### Game Components
- Space ship:<br>
	- is made from two torus.
	- has velocity and direction. Velocity can be increased/decreased by pressing keyboard keys `a` and `d`. Initial speed is 2 unit. Direction can be changed by pressing `left` and `right` arrow keys.
- Planets: are made from spheres with different colors and each planet has two circles around it.<br>
	- Planets are not moving.
- Station: are made from sphere bigger than planets. To mark its front, a simple shape square is placed in front of it. The station’s location does not change, but it has a rotational (angular) speed (initially 0). To increase/decrease rotational speed, keys `j` and `k` can be pressed.
- Tetrahedron : is to mark the front of the space ship

#### Viewings
- The game have different 4 viewing options.

**1.** By pressing `c`(default) the viewer is
switched to the control desk (in front of the tetrahedron) of the spacehip and looks in the
direction that the spaceship moves.

**2.** By pressing `s` the viewer is switched to the front of the station and
looks in the direction of its front. If station is rotating, viewer is rotating also.

**3.** By pressing `t` the viewer is positioned behind and slightly
above the spacehip.

**4.** By pressing `w` the viewer way up on y-axis so that we can see all objects.	

#### Single Step Mode
-Fot the purpose of debugging, when the right mouse button is pressed, the simulation enters paused state(also enters pause state by pressing `p` key). The
state of the simulation is advanced by one step, and then the program outputs all the simulation’s current state to standard output includes the locations, directions and 
speeds of the ship/station. By repeatedly hitting the right button the program will perform consecutive single steps.

#### Implementation

- Implemented with shader based OpenGL(modern OpenGL) and used Gouraud shading for objects.

#### WARNING
If you get error like "illegal non-ASCII character" from glsl files, change vshader.glsl and fshader.glsl file endings from crlf to lf, and then run the program again.

#### Dependencies
- Program should run in `win32` environment and needs `glut` and `opengl` libraries.


#### Yaşar Can Kakdaş
