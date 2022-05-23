#pragma once
#include "Cell.h"
#include "Painter.h"
#include "Random.h"
#include <cassert>
#define _USE_MATH_DEFINES_
#include <math.h>

using std::vector;

class Simulation {
	vector<Cell> Cells;
	Map* pMap;
	Painter* pPainter;

	const double year_day = 365;
	const double day = 150;
	const double brigth = 20;

	float BiasLS = SIMULATION_STARTED_SEA_LEVEL;
	float LS = BiasLS;

	bool IsInMap(int x, int y) {
		return (0 <= x) && (x < MAP_X) && (0 <= y) && (y < MAP_Y);
	}
	uint16_t Photosyntes(int x, int y,int t) {
		double getMap = pMap->GetSunMap(x, y);
		double sin1 = sin(t * (1 / day)) + 1;
		double sin2 = sin(t * (1 / year_day) * (1 / day)) * ((year_day * brigth) / (year_day * 4)) + ((year_day * brigth) / (year_day * 4)) + 1;
		return abs(sin1 * sin2 * getMap);
	}
private:
	bool CellMoveChecker(int x, int y) {
		return IsInMap(x, y) && !pMap->GetVisibleMap(x, y);// && !pMap->IsSea(x,y,LS);
	}

public:
	void Init(int cnt);

	void GeneSwitch();
	void GeneAction();
	void GeneRetarget();
	void Do();

	void SwitchMode() {
		pPainter->SwitchMode();
	}

	void Paint();

	void Finit() {
		delete pMap;
		delete pPainter;
	}
};

