#pragma once
#include <windows.h>
#include <gl/gl.h>
#include "Define.h"
#include "Map.h"
#pragma comment(lib, "opengl32.lib")

class Painter {
	char MapMode = 'V';
public:
	void DrawQuad() {
		glBegin(GL_TRIANGLE_STRIP);

		glVertex2f(0, 0);
		glVertex2f(0, 1);
		glVertex2f(1, 0);
		glVertex2f(1, 1);

		glEnd();
	}

	void Paint(Map& map) {
		glLoadIdentity();
		glTranslatef(-1.0f, -1.0f, 0.0f);
		glScalef(2.0f / MAP_X, 2.0f / MAP_Y, 0.0f);

		
		for (int i = 0;i < MAP_X;i++) {
			for (int j = 0;j < MAP_Y;j++) {
				glPushMatrix();

				glTranslatef(i, j, 0.0f);

				//if (MapMode == 'V')
				glColor3d(map.GetLandMap(i, j), map.GetLandMap(i, j), map.GetLandMap(i, j));
				DrawQuad();

				glPopMatrix();
			}
		}
		
	}
};

