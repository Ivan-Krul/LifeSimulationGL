#pragma once
#include "Random.h"
#include "Perlin.h"
#include "Define.h"
#include "Variables.h"

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

	bool IsInMap(int x, int y) {
		return (0 <= x) && (x < MAP_X) && (0 <= y) && (y < MAP_Y);
	}

	void GenerateMap(int seed) {
		RandomInt* a = new RandomInt(seed);
		PerlinNoise PN[MAP_NUM_OCTAVES];

		for (int o = 0;o < MAP_NUM_OCTAVES;o++) {
			PN[o].Init(a->Next());
		}

		delete a;

		double mn = INFINITY;
		double mx = -INFINITY;

		for (int i = 0;i < MAP_Y;i++) {
			for (int j = 0;j < MAP_X;j++) {

				OptionMap[MAP_Y * j+i].X = 0;

				for (int o = 0;o < MAP_NUM_OCTAVES;o++) {
					double c = 1.0/pow(MAP_DETAIL_CHANGES,double(o));
					double k = pow(MAP_DETAIL_CHANGES, double(o));

					OptionMap[MAP_Y * j + i].X +=
					PN[0].noise(double(j * k*(1.0/MAP_SCALE)) / MAP_X, double(i * k * (1.0 / MAP_SCALE)) / MAP_Y, 0.0)*c;
				}
				OptionMap[MAP_Y * j + i].X = Func(OptionMap[MAP_Y * j + i].X);


				mn = min(OptionMap[MAP_Y * j + i].X, mn);
				mx = max(OptionMap[MAP_Y * j + i].X, mx);
			}
		}

		for (int i = 0;i < MAP_Y;i++) {
			for (int j = 0;j < MAP_X;j++) {
				OptionMap[MAP_Y * j + i].X = (OptionMap[MAP_Y * j + i].X - mn) / (mx - mn);
			}
		}

	}

	void Erode(int cnt) {
		RandomInt random(cnt+GlobalSeed);
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

				if (OptionMap[MAP_Y * cor.X + cor.Y].X == OptionMap[MAP_Y * cord.X + cord.Y].X) {
					OptionMap[MAP_Y * (cord.X) + (cord.Y)].X += 0.01;

					for (int i = -1;i < 2;i++) {
						for (int j = -1;j < 2;j++) {

							if (IsInMap((j + cord.X), (i + cord.Y))) {
								if (OptionMap[MAP_Y * (j + cord.X) + (j + cord.Y)].X - 0.001 > 0)
									OptionMap[MAP_Y * (j + cord.X) + (j + cord.Y)].X -= 0.001;
							}

						}
					}

					break;
				}
				else {
					if (OptionMap[MAP_Y * (cord.X) + (cord.Y)].X - 0.001 > 0)
						OptionMap[MAP_Y * (cord.X) + (cord.Y)].X -= 0.001;

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

				
				S[MAP_Y * (j) + (i)] = (OptionMap[MAP_Y * (j)+(i)].X-(sum/F))*0.00025;
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
