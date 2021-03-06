#pragma once
#include "Random.h"
#include "Perlin.h"
#include "Define.h"
#include "Variables.h"
#include <vector>

using std::vector;

class Map {
	Point3<double>* OptionMap;
	bool* VisibleMap;

	double Func(double x) {
		return pow(x,1);
	}

	bool IsInMap(int x, int y) {
		return (0 <= x) && (x < MAP_X) && (0 <= y) && (y < MAP_Y);
	}
public:
	Map() {
		OptionMap = new Point3<double>[MAP_X * MAP_Y];
		VisibleMap = new bool[MAP_X * MAP_Y];
	}

	void GenerateMap() {
		//RandomInt* a = new RandomInt();
		PerlinNoise PN[MAP_NUM_OCTAVES*3];

		for (int o = 0;o < MAP_NUM_OCTAVES * 3;o++) {
			PN[o].Init(global.GiveSeed());
		}

		//delete a;

		double mnX = INFINITY;
		double mxX = -INFINITY;
		double mnY = INFINITY;
		double mxY = -INFINITY;
		double mnZ = INFINITY;
		double mxZ = -INFINITY;

		for (int i = 0;i < MAP_Y;i++) {
			for (int j = 0;j < MAP_X;j++) {

				OptionMap[MAP_Y * j + i].X = 0;
				OptionMap[MAP_Y * j + i].Y = 0;
				OptionMap[MAP_Y * j + i].Z = 0;

				for (int o = 0;o < MAP_NUM_OCTAVES*3;o++) {
					double c = 1.0 / pow(MAP_DETAIL_CHANGES, double(o % MAP_NUM_OCTAVES));
					double k = pow(MAP_DETAIL_CHANGES, double(o % MAP_NUM_OCTAVES));

					if (o / MAP_NUM_OCTAVES == 0)
						OptionMap[MAP_Y * j + i].X += PN[o].noise(double(j * k * (1.0 / MAP_SCALE)) / MAP_X, double(i * k * (1.0 / MAP_SCALE)) / MAP_Y, 0.0) * c;
					else if (o / MAP_NUM_OCTAVES == 1)
						OptionMap[MAP_Y * j + i].Y += PN[o].noise(double(j * k * (1.0 / MAP_SCALE)) / MAP_X, double(i * k * (1.0 / MAP_SCALE)) / MAP_Y, 0.0) * c;
					else if (o / MAP_NUM_OCTAVES == 2)
						OptionMap[MAP_Y * j + i].Z += PN[o].noise(double(j * k * (1.0 / MAP_SCALE)) / MAP_X, double(i * k * (1.0 / MAP_SCALE)) / MAP_Y, 0.0) * c;

				}
				OptionMap[MAP_Y * j + i].X = Func(OptionMap[MAP_Y * j + i].X);
				OptionMap[MAP_Y * j + i].Y = Func(OptionMap[MAP_Y * j + i].Y);
				OptionMap[MAP_Y * j + i].Z = Func(OptionMap[MAP_Y * j + i].Z);

				mnX = min(OptionMap[MAP_Y * j + i].X, mnX);
				mxX = max(OptionMap[MAP_Y * j + i].X, mxX);
				mnY = min(OptionMap[MAP_Y * j + i].Y, mnY);
				mxY = max(OptionMap[MAP_Y * j + i].Y, mxY);
				mnZ = min(OptionMap[MAP_Y * j + i].Z, mnZ);
				mxZ = max(OptionMap[MAP_Y * j + i].Z, mxZ);
			}
		}

		for (int i = 0;i < MAP_Y;i++) {
			for (int j = 0;j < MAP_X;j++) {
				OptionMap[MAP_Y * j + i].X = (OptionMap[MAP_Y * j + i].X - mnX) / (mxX - mnX);
				OptionMap[MAP_Y * j + i].Y = (OptionMap[MAP_Y * j + i].Y - mnY) / (mxY - mnY);
				OptionMap[MAP_Y * j + i].Z = (OptionMap[MAP_Y * j + i].Z - mnZ) / (mxZ - mnZ);
			}
		}

	}

	double& GetLandMap(int x, int y) {
		return OptionMap[(x % MAP_X) + (y % MAP_Y) * MAP_X].X;
	}

	double& GetSunMap(int x, int y) {
		return OptionMap[(x % MAP_X) + (y % MAP_Y) * MAP_X].Y;
	}

	double& GetMineralMap(int x, int y) {
		return OptionMap[(x % MAP_X) + (y % MAP_Y) * MAP_X].Z;
	}

	bool& GetVisibleMap(int x, int y) {
		return VisibleMap[(x % MAP_X) + (y % MAP_Y) * MAP_X];
	}

	void SetMineralMap(int x, int y,double change) {
		OptionMap[(x % MAP_X) + (y % MAP_Y) * MAP_X].Z += change;
		if (OptionMap[(x % MAP_X) + (y % MAP_Y) * MAP_X].Z < 0)OptionMap[(x % MAP_X) + (y % MAP_Y) * MAP_X].Z = 0;
		else if (OptionMap[(x % MAP_X) + (y % MAP_Y) * MAP_X].Z > 1)OptionMap[(x % MAP_X) + (y % MAP_Y) * MAP_X].Z = 1;
	}

	void SetLandMap(int x, int y, double change) {
		OptionMap[(x % MAP_X) + (y % MAP_Y) * MAP_X].X += change;
		if (OptionMap[(x % MAP_X) + (y % MAP_Y) * MAP_X].X < 0)OptionMap[(x % MAP_X) + (y % MAP_Y) * MAP_X].X = 0;
		else if (OptionMap[(x % MAP_X) + (y % MAP_Y) * MAP_X].X > 1)OptionMap[(x % MAP_X) + (y % MAP_Y) * MAP_X].X = 1;
	}

	void SetVisibleMap(int x, int y, bool change) {
		VisibleMap[(x % MAP_X) + (y % MAP_Y) * MAP_X] = change;
	}

	double GetPlainLandMap(int x, int y) {
		double sum = -OptionMap[MAP_Y * (x)+(y)].X;
		int F = 0;

		for (int ii = -1;ii < 2;ii++) {
			for (int jj = -1;jj < 2;jj++) {

				if (IsInMap((x + jj), (y + ii))) {
					//if()
					sum += OptionMap[MAP_Y * (x + jj) + (y + ii)].X;
					F++;
				}

			}
		}

		return OptionMap[MAP_Y * (x) + (y)].X-(sum / (F*2));

	}

	bool IsSea(unsigned int x, unsigned int y, float l) {
		return OptionMap[(x % MAP_X) + (y % MAP_Y) * MAP_X].X < l;
	}

	~Map() {
		delete[] OptionMap;
		delete[] VisibleMap;
	}
};
