#pragma once
#include "Cell.h"
#include "Painter.h"
#include "Random.h"

using std::vector;

class Simulation {
	vector<Cell> Cells;
	Map* pMap;
	Painter* pPainter;

	bool IsInMap(int x, int y) {
		return (0 <= x) && (x < MAP_X) && (0 <= y) && (y < MAP_Y);
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

