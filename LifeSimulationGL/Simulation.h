#pragma once
#include <list>
#include "Cell.h"
#include "Painter.h"
#include "Random.h"

using std::list;

class Simulation {
	list<Cell> Cells;
	Map* pMap;
	Painter* pPainter;

public:
	Simulation(int cnt);

	void GeneSwitch();
	void GeneAction();
	void GeneRetarget();

	void Paint();
};

