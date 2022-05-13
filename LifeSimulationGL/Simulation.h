#pragma once
#include <list>
#include "Cell.h"
#include "Map.h"
#include "Painter.h"

using std::list;

class Simulation {
	list<Cell> Cells;
	Map* pMap;
	Painter* pPainter;

	Simulation();

};

