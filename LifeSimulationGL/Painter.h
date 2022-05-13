#pragma once
#include <windows.h>
#include <gl/gl.h>
#include "Define.h"
#include "Map.h"
#pragma comment(lib, "opengl32.lib")

class Painter {
	char MapMode = 0;
public:
	void SwitchMode() {
		MapMode= ++MapMode%6;
	}

	void DrawQuad() {
		glBegin(GL_TRIANGLE_STRIP);

		glVertex2f(0, 0);
		glVertex2f(0, 1);
		glVertex2f(1, 0);
		glVertex2f(1, 1);

		glEnd();
	}

	void Paint(Map& map,float& t) {
		glLoadIdentity();
		glTranslatef(-1.0f, -1.0f, 0.0f);
		glScalef(WINDOW_RELATION / MAP_X, 2.0f / MAP_Y, 0.0f);

		double mn = INFINITY;
		double mx = -INFINITY;
		for (int i = 0;i < MAP_X;i++) {
			for (int j = 0;j < MAP_Y;j++) {
				mn = min(mn, map.GetPlainLandMap(i, j));
				mx = max(mx, map.GetPlainLandMap(i, j));
			}
		}


		
		for (int i = 0;i < MAP_X;i++) {
			for (int j = 0;j < MAP_Y;j++) {
				glPushMatrix();

				glTranslatef(i, j, 0.0f);
				switch (MapMode)
				{
				case 0:
					if (map.GetLandMap(i, j) > t) {
						if (map.GetLandMap(i, j) - t < 0.01)glColor3d(0.6, 0.6, 0.1);
						else {
							double S = (map.GetPlainLandMap(i, j) - mn) / (mx - mn);

							double r1 = 0.3;
							double g1 = 0.7;
							double b1 = 0.1;
							double r2 = 0.3;
							double g2 = 0.2;
							double b2 = 0.05;
							glColor3d(((r1 - r2) * S + r2)  * (map.GetLandMap(i, j)+0.5*0.5), ((g1 - g2) * S + g2) * (map.GetLandMap(i, j) + 0.5 * 0.5),( (b1 - b2) * S + b2) * (map.GetLandMap(i, j) + 0.5 * 0.5));
						}
					}
					else glColor3d(map.GetLandMap(i, j) - 0.3, map.GetLandMap(i, j) - 0.3, map.GetLandMap(i, j));

					DrawQuad();
					break;
				case 1:
					if (map.GetLandMap(i, j) > t) {
						glColor3d(map.GetLandMap(i, j), map.GetLandMap(i, j), map.GetLandMap(i, j));
					}
					else glColor3d(map.GetLandMap(i, j) - 0.3, map.GetLandMap(i, j) - 0.3, map.GetLandMap(i, j));

					DrawQuad();
					break;
				case 2:
					glColor3d(map.GetLandMap(i, j), map.GetLandMap(i, j), map.GetLandMap(i, j));

					DrawQuad();
					break;
				case 3:
					glColor3d(map.GetSunMap(i, j), map.GetSunMap(i, j), map.GetSunMap(i, j)-0.2);

					DrawQuad();
					break;
				case 4:
					glColor3d(map.GetLandMap(i, j)-0.1, map.GetLandMap(i, j)-0.1, map.GetLandMap(i, j));

					DrawQuad();
					break;
				case 5:
					//glColor3d(0, 0, 0);
					break;
				default:
					break;
				}
				//if (MapMode == 'V')

				glPopMatrix();
			}
		}
		
	}
};

