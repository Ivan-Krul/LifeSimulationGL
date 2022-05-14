#pragma once
#include "Random.h"
#include "Perlin.h"
#include "Define.h"
#include "Variables.h"
#include <vector>

class Map {
	Point3<double>* OptionMap;
	bool* VisibleMap;

	double Func(double x) {
		return pow(x,1);
	}
public:
	Map() {
		OptionMap = new Point3<double>[MAP_X * MAP_Y];
		VisibleMap = new bool[MAP_X * MAP_Y];
	}

	void GenerateMap(int seed) {
		RandomInt* a = new RandomInt(seed);
		PerlinNoise PN[MAP_NUM_OCTAVES*3];

		for (int o = 0;o < MAP_NUM_OCTAVES;o++) {
			PN[o].Init(a->Next());
		}

		delete a;

		double mnX = INFINITY;
		double mxX = -INFINITY;
		double mnY = INFINITY;
		double mxY = -INFINITY;
		double mnZ = INFINITY;
		double mxZ = -INFINITY;

		for (int i = 0;i < MAP_Y;i++) {
			for (int j = 0;j < MAP_X;j++) {

				OptionMap[MAP_Y * j+i].X = 0;
				OptionMap[MAP_Y * j + i].Y = 0;
				OptionMap[MAP_Y * j + i].Z = 0;

				for (int o = 0;o < MAP_NUM_OCTAVES*3;o++) {
					double c = 1.0 / pow(MAP_DETAIL_CHANGES, double(o % MAP_NUM_OCTAVES));
					double k = pow(MAP_DETAIL_CHANGES, double(o % MAP_NUM_OCTAVES));

					if (o / MAP_NUM_OCTAVES == 0)
						OptionMap[MAP_Y * j + i].X += PN[o].noise(double(j * k*(1.0/MAP_SCALE)) / MAP_X, double(i * k * (1.0 / MAP_SCALE)) / MAP_Y, 0.0)*c;
					else if (o / MAP_NUM_OCTAVES == 1)
						OptionMap[MAP_Y * j + i].Y += PN[o].noise(double(j * k * (1.0 / MAP_SCALE)) / MAP_X, double(i * k * (1.0 / MAP_SCALE)) / MAP_Y, 0.0) * c;
					else OptionMap[MAP_Y * j + i].X += PN[o].noise(double(j * k * (1.0 / MAP_SCALE)) / MAP_X, double(i * k * (1.0 / MAP_SCALE)) / MAP_Y, 0.0) * c;

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

	void Erode(int cnt) {
		RandomInt random(cnt+GlobalSeed);
		std::vector<Point2<int>> list;
		Point2<int> cord;
		for (int s = 0;s < cnt;s++) {
			cord.X = random.Next(MAP_X);
			cord.Y = random.Next(MAP_Y);

			int d = 0;
			while (d<100) {
				Point2<int> cor;
				cor.X = cord.X;
				cor.Y = cord.Y;
				double mn = OptionMap[MAP_Y * cord.X + cord.Y].X;

				for (int i = -1;i < 2;i++) {
					for (int j = -1;j < 2;j++) {

						if (IsInMap((j+cord.X), (i + cord.Y))) {
							if (mn > OptionMap[MAP_Y * (j + cord.X) + (i + cord.Y)].X) {
								mn = OptionMap[MAP_Y * (j + cord.X) + (i + cord.Y)].X;
								cor.X = (j + cord.X);
								cor.Y = (i + cord.Y);
							}
						}
							
					}
				}

				bool isInList = false;
				for (int i = 0;i < list.size();i++) {
					if(cor.X==list[i].X && cor.Y == list[i].Y)
						isInList = true;
				}

				if (isInList) {
					OptionMap[MAP_Y * (cord.X) + (cord.Y)].X += 0.001;

					for (int i = -1;i < 2;i++) {
						for (int j = -1;j < 2;j++) {

							if (IsInMap((j + cord.X), (i + cord.Y))) {
								if (OptionMap[MAP_Y * (j + cord.X) + (j + cord.Y)].X - 0.0001 > 0)
									OptionMap[MAP_Y * (j + cord.X) + (j + cord.Y)].X -= 0.0001;
							}

						}
					}

					break;
				}
				else {
					if (OptionMap[MAP_Y * (cord.X) + (cord.Y)].X - 0.0001 > 0)
						OptionMap[MAP_Y * (cord.X) + (cord.Y)].X -= 0.0001;

					list.push_back(cord);
					cord.X = cor.X;
					cord.Y = cor.Y;
				}
				d++;
			}
			Smooth();
		}
	}

	void Smooth() {
		int F;
		double sum;

		double* S = new double[MAP_X * MAP_Y];

		for (int i = 0;i < MAP_Y;i++) {
			for (int j = 0;j < MAP_X;j++) {
				sum = 0;
				F = 0;

				for (int ii = -1;ii < 2;ii++) {
					for (int jj = -1;jj < 2;jj++) {

						if (IsInMap((j + jj), (i + ii))) {
							sum += OptionMap[MAP_Y * (j + jj) + (i + ii)].X;
							F++;
						}

					}
				}

				
				S[MAP_Y * (j) + (i)] = (OptionMap[MAP_Y * (j)+(i)].X-(sum/F))*0.000025;
			}
		}

		Normalise(S);
	}

	void Normalise(double* S) {
		double mn = INFINITY;
		double mx = -INFINITY;

		for (int i = 0;i < MAP_Y;i++) {
			for (int j = 0;j < MAP_X;j++) {
				mn = min(OptionMap[MAP_Y * j + i].X- S[MAP_Y * j + i], mn);
				mx = max(OptionMap[MAP_Y * j + i].X - S[MAP_Y * j + i], mx);
			}
		}

		for (int i = 0;i < MAP_Y;i++) {
			for (int j = 0;j < MAP_X;j++) {
				OptionMap[MAP_Y * j + i].X = ((OptionMap[MAP_Y * j + i].X - S[MAP_Y * j + i] )- mn) / (mx - mn);
			}
		}
		delete[] S;
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

		return OptionMap[MAP_Y * (x) + (y)].X-(sum / F);

	}

	~Map() {
		delete[] OptionMap;
		delete[] VisibleMap;
	}
};
