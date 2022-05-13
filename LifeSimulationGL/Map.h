#pragma once
#include "Random.h"
#include "Perlin.h"
#include "Define.h"
#include "Variables.h"

class Map {
	Point3<double>* OptionMap;
	bool* VisibleMap;
public:
	Map() {
		OptionMap = new Point3<double>[MAP_X * MAP_Y];
		VisibleMap = new bool[MAP_X * MAP_Y];
	}

	void GenerateMap() {
		
		PerlinNoise PN[MAP_NUM_OCTAVES];


		for (int i = 0;i < MAP_Y;i++) {
			for (int j = 0;j < MAP_X;j++) {

				OptionMap[MAP_Y * j+i].X = 0;

				//for (int o = 0;o < MAP_NUM_OCTAVES;o++) {
				
				OptionMap[MAP_Y * j + i].X = PN[0].noise(double(j*4)/ MAP_X, double(i*4) / MAP_Y, 0.5);

				if (OptionMap[MAP_Y * j + i].X > 1 || OptionMap[MAP_Y * j + i].X < 0)
					Beep(1000,1000);
						//PN[o].noise(j, i, 0) * 1.0/((o==0)?1:(MAP_DETAIL_CHANGES*o));
				//}
			}
		}

	}

	double GetLandMap(int x, int y) {
		return OptionMap[(x % MAP_X) + (y % MAP_Y) * MAP_X].X;
	}

	double GetSunMap(int x, int y) {
		return OptionMap[(x % MAP_X) + (y % MAP_Y) * MAP_X].Y;
	}

	double GetMineralMap(int x, int y) {
		return OptionMap[(x % MAP_X) + (y % MAP_Y) * MAP_X].Z;
	}

	bool GetVisibleMap(int x, int y) {
		return VisibleMap[(x % MAP_X) + (y % MAP_Y) * MAP_X];
	}

	void SetMineralMap(int x, int y,double change) {
		OptionMap[(x % MAP_X) + (y % MAP_Y) * MAP_X].Z += change;
	}

	void SetVisibleMap(int x, int y, bool change) {
		VisibleMap[(x % MAP_X) + (y % MAP_Y) * MAP_X] = change;
	}

	~Map() {
		delete[] OptionMap;
		delete[] VisibleMap;
	}
};
