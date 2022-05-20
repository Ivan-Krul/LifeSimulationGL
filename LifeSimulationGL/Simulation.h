#pragma once
#include "Cell.h"
#include "Painter.h"
#include "Random.h"
#include <cassert>

using std::vector;

class Simulation {
	vector<Cell> Cells;
	Map* pMap;
	Painter* pPainter;

	float BiasLS = SIMULATION_STARTED_SEA_LEVEL;
	float LS = BiasLS;

	bool IsInMap(int x, int y) {
		return (0 <= x) && (x < MAP_X) && (0 <= y) && (y < MAP_Y);
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

