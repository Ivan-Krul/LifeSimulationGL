#include "Simulation.h"

void Simulation::Init(int cnt) {
	RandomShort random;

	pPainter = new Painter();
	pMap = new Map();
	pMap->GenerateMap();

	for (int i = 0;i < cnt;i++) {
		short x = random.Next(MAP_X);
		short y = random.Next(MAP_Y);

		while (!pMap->GetVisibleMap(x, y) || pMap->IsSea(x, y, LS)) {
			x = random.Next(MAP_X);
			y = random.Next(MAP_Y);
		}

		short m[2] = { x,y };
		Cells.push_back(celular(m));
	}
}

void Simulation::GeneSwitch() {
	for (int iter = 0; iter != Cells.size(); iter++) {
		int F = 0;
		celular& celula = Cells[iter];
		for (int ii = -1;ii < 2;ii++) {
			for (int jj = -1;jj < 2;jj++) {

				if (pMap->GetVisibleMap(ii + celula._pos[0], jj + celula._pos[1]))
					F++;

			}
		}
		Cells[iter].switch_command(F);
	}
}

void Simulation::GeneAction() {
	int CM;
	int AR;
	RandomInt raan;

	size_t size = Cells.size();

	for (int iter = 0; iter != size; iter++) {
		celular& celula = Cells[iter];

		CM = celula.get_command();
		AR = celula.get_argument();

		short x = celula._pos[0];
		short y = celula._pos[1];

		switch (CM) {
			case Move: {
				switch (AR) {
					case 0:
						y++;
						if (CellMoveChecker(x, y))
							celula.set_cordinates(x, y);
						break;
					case 1:
						x++;
						y++;
						if (CellMoveChecker(x, y))
							celula.set_cordinates(x, y);
						break;
					case 2:
						x++;
						if (CellMoveChecker(x, y))
							celula.set_cordinates(x, y);
						break;
					case 3:
						x++;
						y--;
						if (CellMoveChecker(x, y))
							celula.set_cordinates(x, y);
						break;
					case 4:
						y--;
						if (CellMoveChecker(x, y))
							celula.set_cordinates(x, y);
						break;
					case 5:
						x--;
						y--;
						if (CellMoveChecker(x, y))
							celula.set_cordinates(x, y);
						break;
					case 6:
						x--;
						if (CellMoveChecker(x, y))
							celula.set_cordinates(x, y);
						break;
					case 7:
						x--;
						y++;
						if (CellMoveChecker(x, y))
							celula.set_cordinates(x, y);
						break;
				}
				celula.change_energy(-1);
				break;
			}
			/*case Divide:
				{
					short xx = x;
					short yy = y;
					switch (AR) {
						case 0:
							{
								y++;
								if (CellMoveChecker(x, y)) {
									celula.SetCoord(x, y);
									celular nextCell;
									Cells.push_back(nextCell);
									nextCell.Init(celula, 0);
								}
								celula.SetCoord(xx, yy);
								break;
							}
						case 1:
							{
								x++;
								y++;
								if (CellMoveChecker(x, y)) {
									celula.SetCoord(x, y);
									celular nextCell;
									Cells.push_back(nextCell);
									Cells[Cells.size() - 1].Init(celula, 0);
								}
								celula.SetCoord(xx, yy);
								break;
							}
						case 2:
							{
								x++;
								if (CellMoveChecker(x, y)) {
									celula.SetCoord(x, y);
									celular nextCell;
									Cells.push_back(nextCell);
									nextCell.Init(celula, 0);
								}
								celula.SetCoord(xx, yy);
								break;
							}
						case 3:
							{
								x++;
								y--;
								if (CellMoveChecker(x, y)) {
									celula.SetCoord(x, y);
									celular nextCell;
									Cells.push_back(nextCell);
									nextCell.Init(celula, 0);
								}
								celula.SetCoord(xx, yy);
								break;
							}
						case 4:
							{
								y--;
								if (CellMoveChecker(x, y)) {
									celula.SetCoord(x, y);
									celular nextCell;
									Cells.push_back(nextCell);
									nextCell.Init(celula, 0);
								}
								celula.SetCoord(xx, yy);
								break;
							}
						case 5:
							{
								x--;
								y--;
								if (CellMoveChecker(x, y)) {
									celula.SetCoord(x, y);
									celular nextCell;
									Cells.push_back(nextCell);
									nextCell.Init(celula, 0);
								}
								celula.SetCoord(xx, yy);
								break;
							}
						case 6:
							{
								x--;
								if (CellMoveChecker(x, y)) {
									celula.SetCoord(x, y);
									celular nextCell;
									Cells.push_back(nextCell);
									nextCell.Init(celula, 0);
								}
								celula.SetCoord(xx, yy);
								break;
							}
						case 7:
							{
								x--;
								y++;
								if (CellMoveChecker(x, y)) {
									celula.SetCoord(x, y);
									celular nextCell;
									Cells.push_back(nextCell);
									nextCell.Init(celula, 0);
								}
								celula.SetCoord(xx, yy);
								break;
							}
					}
					break;
				}*/
			case Photosyn: {
					switch (AR) {
						case 0:
							y++;
							if (IsInMap(x, y))
								celula.change_energy(Photosyntes(x, y, pPainter->GetT()));
							break;
						case 1:
							x++;
							y++;
							if (IsInMap(x, y))
								celula.change_energy(Photosyntes(x, y, pPainter->GetT()));
							break;
						case 2:
							x++;
							if (IsInMap(x, y))
								celula.change_energy(Photosyntes(x, y, pPainter->GetT()));
							break;
						case 3:
							x++;
							y--;
							if (IsInMap(x, y))
								celula.change_energy(Photosyntes(x, y, pPainter->GetT()));
							break;
						case 4:
							y--;
							if (IsInMap(x, y))
								celula.change_energy(Photosyntes(x, y, pPainter->GetT()));
							break;
						case 5:
							x--;
							y--;
							if (IsInMap(x, y))
								celula.change_energy(Photosyntes(x, y, pPainter->GetT()));
							break;
						case 6:
							x--;
							if (IsInMap(x, y))
								celula.change_energy(Photosyntes(x, y, pPainter->GetT()));
							break;
						case 7:
							x--;
							y++;
							if (IsInMap(x, y))
								celula.change_energy(Photosyntes(x, y, pPainter->GetT()));
							break;
					}
					break;
				}
			case EatCell: {
					switch (AR) {
						case 0:
							y++;
							if (IsInMap(x, y))
								for (int i = 0;i < size;i++) {
									if (Cells[i]._pos[0] == x && Cells[i]._pos[1] == y) {
										Cells[i].change_energy(-SIMULATION_COUNT_MEAT);
										celula.change_energy(SIMULATION_COUNT_MEAT);
										break;
									}
								}
							break;
						case 1:
							x++;
							y++;
							if (IsInMap(x, y))
								for (int i = 0;i < size;i++) {
									if (Cells[i]._pos[0] == x && Cells[i]._pos[1] == y) {
										Cells[i].change_energy(-SIMULATION_COUNT_MEAT);
										celula.change_energy(SIMULATION_COUNT_MEAT);
										break;
									}
								}
							break;
						case 2:
							x++;
							if (IsInMap(x, y))
								for (int i = 0;i < size;i++) {
									if (Cells[i]._pos[0] == x && Cells[i]._pos[1] == y) {
										Cells[i].change_energy(-SIMULATION_COUNT_MEAT);
										celula.change_energy(SIMULATION_COUNT_MEAT);
										break;
									}
								}
							break;
						case 3:
							x++;
							y--;
							if (IsInMap(x, y))
								for (int i = 0;i < size;i++) {
									if (Cells[i]._pos[0] == x && Cells[i]._pos[1] == y) {
										Cells[i].change_energy(-SIMULATION_COUNT_MEAT);
										celula.change_energy(SIMULATION_COUNT_MEAT);
										break;
									}
								}
							break;
						case 4:
							y--;
							if (IsInMap(x, y))
								for (int i = 0;i < size;i++) {
									if (Cells[i]._pos[0] == x && Cells[i]._pos[1] == y) {
										Cells[i].change_energy(-SIMULATION_COUNT_MEAT);
										celula.change_energy(SIMULATION_COUNT_MEAT);
										break;
									}
								}
							break;
						case 5:
							x--;
							y--;
							if (IsInMap(x, y))
								for (int i = 0;i < size;i++) {
									if (Cells[i]._pos[0] == x && Cells[i]._pos[1] == y) {
										Cells[i].change_energy(-SIMULATION_COUNT_MEAT);
										celula.change_energy(SIMULATION_COUNT_MEAT);
										break;
									}
								}
							break;
						case 6:
							x--;
							if (IsInMap(x, y))
								for (int i = 0;i < size;i++) {
									if (Cells[i]._pos[0] == x && Cells[i]._pos[1] == y) {
										Cells[i].change_energy(-SIMULATION_COUNT_MEAT);
										celula.change_energy(SIMULATION_COUNT_MEAT);
										break;
									}
								}
							break;
						case 7:
							x--;
							y++;
							if (IsInMap(x, y))
								for (int i = 0;i < size;i++) {
									if (Cells[i]._pos[0] == x && Cells[i]._pos[1] == y) {
										Cells[i].change_energy(-SIMULATION_COUNT_MEAT);
										celula.change_energy(SIMULATION_COUNT_MEAT);
										break;
									}
								}
							break;
					}
					break;
				}
			case Mineral: {
					switch (AR) {
						case 0:
							{
								y++;
								if (IsInMap(x, y)) {
									celula.change_energy(SIMULATION_COUNT_MINERAL);
									pMap->SetMineralMap(x, y, -0.05);
								}
								break;
							}
						case 1:
							{
								x++;
								y++;
								if (IsInMap(x, y)) {
									celula.change_energy(SIMULATION_COUNT_MINERAL);
									pMap->SetMineralMap(x, y, -0.05);
								}
								break;
							}
						case 2:
							{
								x++;
								if (IsInMap(x, y)) {
									celula.change_energy(SIMULATION_COUNT_MINERAL);
									pMap->SetMineralMap(x, y, -0.05);
								}
								break;
							}
						case 3:
							{
								x++;
								y--;
								if (IsInMap(x, y)) {
									celula.change_energy(SIMULATION_COUNT_MINERAL);
									pMap->SetMineralMap(x, y, -0.05);
								}
								break;
							}
						case 4:
							{
								y--;
								if (IsInMap(x, y)) {
									celula.change_energy(SIMULATION_COUNT_MINERAL);
									pMap->SetMineralMap(x, y, -0.05);
								}
								break;
							}
						case 5:
							{
								x--;
								y--;
								if (IsInMap(x, y)) {
									celula.change_energy(SIMULATION_COUNT_MINERAL);
									pMap->SetMineralMap(x, y, -0.05);
								}
								break;
							}
						case 6:
							{
								x--;
								if (IsInMap(x, y)) {
									celula.change_energy(SIMULATION_COUNT_MINERAL);
									pMap->SetMineralMap(x, y, -0.05);
								}
								break;
							}
						case 7:
							{
								x--;
								y++;
								if (IsInMap(x, y)) {
									celula.change_energy(SIMULATION_COUNT_MINERAL);
									pMap->SetMineralMap(x, y, -0.05);
								}
								break;
							}
					}
					break;
				}
			default:
				break;
		}

		assert(x - celula._pos[0] + 1 < 3);
		assert(y - celula._pos[1] + 1 < 3);
		assert(AR < 8);
		assert(0 <= AR);
		assert(CM < 8);
		assert(0 <= CM);
		celula.change_energy(-1);
	}
}

void Simulation::GeneRetarget() {
	for (int iter = Cells.size() - 1; iter > -1; iter--) {
		celular& celula = Cells[iter];
		short& cordX = Cells[iter]._pos[0];
		short& cordY = Cells[iter]._pos[1];

		if (Cells[iter].get_energy() <= 0 || pMap->IsSea(cordX, cordY, LS)) {


			for (int ii = -1;ii < 2;ii++) {
				for (int jj = -1;jj < 2;jj++) {

					if (IsInMap((cordX + jj), (cordY + ii)) && (ii != 0 || jj != 0)) {
						pMap->SetMineralMap(cordX + jj, cordY + ii, 0.1);
					}

				}
			}

			Cells.erase(Cells.begin() + iter);
		}
	}
}

void Simulation::Paint() {
	LS = sinf(pPainter->GetT() * SIMULATION_SEA_FREQUENCY) * SIMULATION_SEA_AMPLITUDE + BiasLS;
	assert(0 <= LS && LS < 1);
	for (int i = 0;i < MAP_X;i++)
		for (int j = 0;j < MAP_Y;j++)
			pMap->SetVisibleMap(i, j, false);

	for (int iter = Cells.size() - 1; iter > -1; iter--) {
		pMap->SetVisibleMap(Cells[iter]._pos[0], Cells[iter]._pos[1], true);
	}
	//Do();

	pPainter->Paint(*pMap, Cells, LS);
}
