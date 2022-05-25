#pragma once
#include <windows.h>
#include <gl/gl.h>
#include <string>
#include "Define.h"
#include "celular.h"
#include "Map.h"
#pragma comment(lib, "opengl32.lib")

class Painter {
	char MapMode = 0;
	unsigned long long T = 0;
public:
	void SwitchMode() {
		MapMode= ++MapMode%6;
	}

	void line(double x1, double y1, double x2, double y2) { glVertex2f(x1, y1);glVertex2f(x2, y2); }

	void ShowNumber(int num) {
		glBegin(GL_LINES);
		if (num == '"' || num == '#' || num == '$' || num == '%' || num == '&' || num == '\'' || num == '(' ||
			num == '0' || num == '4' || num == '5' || num == '6' || num == '8' || num == '9' ||
			num == 'L' || num == 'V'
			) line(0.15, 0.85, 0.15, 0.5);
		if (num == '#' || num == '$' || num == '&' || num == '(' ||
			num == '0' || num == '2' || num == '6' || num == '8' ||
			num == 'L'
			) line(0.15, 0.5, 0.15, 0.15);
		if (num == '$' || num == '%' || num == '&' || num == '(' || num == ')' ||
			num == '0' || num == '2' || num == '3' || num == '5' || num == '6' || num == '7' || num == '8' || num == '9'
			
			) line(0.15, 0.85, 0.85, 0.85);
		if (num == '$' || num == '&' ||
			num == '2' || num == '3' || num == '4' || num == '5' || num == '6' || num == '8' || num == '9' || num == ':'
			
			) line(0.15, 0.5, 0.85, 0.5);
		if (num == '$' || num == '%' || num == '&' || num == '(' || num == ')' ||
			num == '0' || num == '2' || num == '3' || num == '5' || num == '6' || num == '8' || num == '9' || num == ':' ||
			num == 'L' || num == 'V' 
			) line(0.15, 0.15, 0.85, 0.15);
		if (num == '!' || num == '"' || num == '#' || num == '&' || num == ')' ||
			num == '0' || num == '1' || num == '2' || num == '3' || num == '4' || num == '7' || num == '8' || num == '9' ||
			num == 'V'
			) line(0.85, 0.5, 0.85, 0.85);
		if (num == '%' || num == ')' ||
			num == '0' || num == '1' || num == '3' || num == '4' || num == '5' || num == '6' || num == '7' || num == '8' || num == '9' ||
			num == 'V'
			) line(0.85, 0.5, 0.85, 0.15);
		glEnd();
	}

	void DrawInterface() {
		glColor3i(1, 0, 0);
		glLineWidth(2);
		unsigned long long gT = T;
		int s = 0;

		while (gT != 0) {
			glPushMatrix();
			
			double X = ((MAP_X)*WINDOW_RELATION)*0.85;
			double Y = (MAP_Y) * 0.05;
			//glTranslatef(1, 1, 0);
			glScalef(2.5f, 5.0f, 0.0f);
			X /= 2.5;
			Y /= 5.0;

			glTranslatef(X - (s * 1.0), Y, 0.0f);
			glColor3f(1, 1, 1);
			//DrawQuad();
			ShowNumber(std::to_string(gT % 10)[0]);
			glEnd();
			glPopMatrix();
			s++;
			gT /= 10;
		}
	}

	void DrawQuad() {
		glBegin(GL_TRIANGLE_STRIP);

		glVertex2f(0, 0);
		glVertex2f(0, 1);
		glVertex2f(1, 0);
		glVertex2f(1, 1);

		glEnd();
	}

	unsigned long long GetT() {
		return T;
	}

	void Paint(Map& map, vector<celular>& cell, float& t) {
		glLoadIdentity();
		glTranslatef(-1.0f, -1.0f, 0.0f);
		glScalef(WINDOW_RELATION * 0.9 / MAP_X, 2.0f / MAP_Y, 0.0f);

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
				if (!map.GetVisibleMap(i, j)) {
					switch (MapMode) {
						case 0:

							if (map.GetLandMap(i, j) > t) {

								if (map.GetLandMap(i, j) - t < 0.01)
									glColor3d(0.6, 0.6, 0.1);
								else {
									double S = (map.GetPlainLandMap(i, j) - mn) / (mx - mn);
									double r1 = 0.3;
									double g1 = 0.7;
									double b1 = 0.1;
									double r2 = 0.3;
									double g2 = 0.2;
									double b2 = 0.05;

									glColor3d(
										((r1 - r2) * S + r2) * (map.GetLandMap(i, j) + 0.5 * 0.5),
										((g1 - g2) * S + g2) * (map.GetLandMap(i, j) + 0.5 * 0.5),
										((b1 - b2) * S + b2) * (map.GetLandMap(i, j) + 0.5 * 0.5));
								}

							}
							else glColor3d(map.GetLandMap(i, j) - 0.3, map.GetLandMap(i, j) - 0.3, map.GetLandMap(i, j));

							DrawQuad();
							break;
						case 1:
							if (map.GetLandMap(i, j) > t)
								glColor3d(map.GetLandMap(i, j), map.GetLandMap(i, j), map.GetLandMap(i, j));
							else
								glColor3d(map.GetLandMap(i, j) - 0.3, map.GetLandMap(i, j) - 0.3, map.GetLandMap(i, j));

							DrawQuad();
							break;
						case 2:
							glColor3d(map.GetLandMap(i, j), map.GetLandMap(i, j), map.GetLandMap(i, j));

							DrawQuad();
							break;
						case 3:
							glColor3d(map.GetSunMap(i, j), map.GetSunMap(i, j), map.GetSunMap(i, j) - 0.2);

							DrawQuad();
							break;
						case 4:
							glColor3d(map.GetMineralMap(i, j) - 0.1, map.GetMineralMap(i, j) - 0.1, map.GetMineralMap(i, j));
							DrawQuad();
							break;
						case 5:
							break;
						default:
							break;
					}
				}
				else {
					for (int c = 0;c < cell.size();c++) {
						short cordX = cell[c]._pos[0];
						short cordY = cell[c]._pos[0];
						if (cordX == i && cordY == j) {
							glColor3ub(cell[c].get_color(0), cell[c].get_color(1), cell[c].get_color(2));
							break;
						}

					}
					DrawQuad();
				}
				glPopMatrix();
			}
		}

		DrawInterface();

		T++;
	}
};
 
