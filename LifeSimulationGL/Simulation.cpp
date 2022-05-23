#include "Simulation.h"

void Simulation::Init(int cnt) {
	RandomShort random;

	pPainter = new Painter();
	pMap = new Map();
	pMap->GenerateMap();

	Cell cll;

	for (int i = 0;i < cnt;i++) {
		short x = random.Next(MAP_X);
		short y = random.Next(MAP_Y);

		while (!pMap->GetVisibleMap(x, y) || pMap->IsSea(x, y, LS)) {
			x = random.Next(MAP_X);
			y = random.Next(MAP_Y);
		}

		COORD S = { x,y };
		Cells.push_back(cll);
		Cells[Cells.size() - 1].Init(S);
	}
}

void Simulation::GeneSwitch() {
	for (int iter = 0; iter != Cells.size(); iter++) {
		int F = 0;
		Cell& cell = Cells[iter];
		for (int ii = -1;ii < 2;ii++) {
			for (int jj = -1;jj < 2;jj++) {

				if (pMap->GetVisibleMap(ii + cell.GetCoord().X, jj + cell.GetCoord().Y))
					F++;

			}
		}
		Cells[iter].SwitchCommand(F);
	}
}

void Simulation::GeneAction() {
	int CM;
	int AR;
	RandomInt raan;

	size_t size = Cells.size();

	for (int iter = 0; iter != size; iter++) {
		Cell& cell = Cells[iter];

		CM = cell.GetGene();
		AR = cell.GetArgument();

		short x = cell.GetCoord().X;
		short y = cell.GetCoord().Y;

		switch (CM) {
			case Move: {
				switch (AR) {
					case 0:
						y++;
						if (CellMoveChecker(x, y))
							cell.SetCoord(x, y);
						break;
					case 1:
						x++;
						y++;
						if (CellMoveChecker(x, y))
							cell.SetCoord(x, y);
						break;
					case 2:
						x++;
						if (CellMoveChecker(x, y))
							cell.SetCoord(x, y);
						break;
					case 3:
						x++;
						y--;
						if (CellMoveChecker(x, y))
							cell.SetCoord(x, y);
						break;
					case 4:
						y--;
						if (CellMoveChecker(x, y))
							cell.SetCoord(x, y);
						break;
					case 5:
						x--;
						y--;
						if (CellMoveChecker(x, y))
							cell.SetCoord(x, y);
						break;
					case 6:
						x--;
						if (CellMoveChecker(x, y))
							cell.SetCoord(x, y);
						break;
					case 7:
						x--;
						y++;
						if (CellMoveChecker(x, y))
							cell.SetCoord(x, y);
						break;
				}
				cell.ChangeEnergy(-1);
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
									cell.SetCoord(x, y);
									Cell nextCell;
									Cells.push_back(nextCell);
									nextCell.Init(cell, 0);
								}
								cell.SetCoord(xx, yy);
								break;
							}
						case 1:
							{
								x++;
								y++;
								if (CellMoveChecker(x, y)) {
									cell.SetCoord(x, y);
									Cell nextCell;
									Cells.push_back(nextCell);
									Cells[Cells.size() - 1].Init(cell, 0);
								}
								cell.SetCoord(xx, yy);
								break;
							}
						case 2:
							{
								x++;
								if (CellMoveChecker(x, y)) {
									cell.SetCoord(x, y);
									Cell nextCell;
									Cells.push_back(nextCell);
									nextCell.Init(cell, 0);
								}
								cell.SetCoord(xx, yy);
								break;
							}
						case 3:
							{
								x++;
								y--;
								if (CellMoveChecker(x, y)) {
									cell.SetCoord(x, y);
									Cell nextCell;
									Cells.push_back(nextCell);
									nextCell.Init(cell, 0);
								}
								cell.SetCoord(xx, yy);
								break;
							}
						case 4:
							{
								y--;
								if (CellMoveChecker(x, y)) {
									cell.SetCoord(x, y);
									Cell nextCell;
									Cells.push_back(nextCell);
									nextCell.Init(cell, 0);
								}
								cell.SetCoord(xx, yy);
								break;
							}
						case 5:
							{
								x--;
								y--;
								if (CellMoveChecker(x, y)) {
									cell.SetCoord(x, y);
									Cell nextCell;
									Cells.push_back(nextCell);
									nextCell.Init(cell, 0);
								}
								cell.SetCoord(xx, yy);
								break;
							}
						case 6:
							{
								x--;
								if (CellMoveChecker(x, y)) {
									cell.SetCoord(x, y);
									Cell nextCell;
									Cells.push_back(nextCell);
									nextCell.Init(cell, 0);
								}
								cell.SetCoord(xx, yy);
								break;
							}
						case 7:
							{
								x--;
								y++;
								if (CellMoveChecker(x, y)) {
									cell.SetCoord(x, y);
									Cell nextCell;
									Cells.push_back(nextCell);
									nextCell.Init(cell, 0);
								}
								cell.SetCoord(xx, yy);
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
								cell.ChangeEnergy(Photosyntes(x, y, pPainter->GetT()));
							break;
						case 1:
							x++;
							y++;
							if (IsInMap(x, y))
								cell.ChangeEnergy(Photosyntes(x, y, pPainter->GetT()));
							break;
						case 2:
							x++;
							if (IsInMap(x, y))
								cell.ChangeEnergy(Photosyntes(x, y, pPainter->GetT()));
							break;
						case 3:
							x++;
							y--;
							if (IsInMap(x, y))
								cell.ChangeEnergy(Photosyntes(x, y, pPainter->GetT()));
							break;
						case 4:
							y--;
							if (IsInMap(x, y))
								cell.ChangeEnergy(Photosyntes(x, y, pPainter->GetT()));
							break;
						case 5:
							x--;
							y--;
							if (IsInMap(x, y))
								cell.ChangeEnergy(Photosyntes(x, y, pPainter->GetT()));
							break;
						case 6:
							x--;
							if (IsInMap(x, y))
								cell.ChangeEnergy(Photosyntes(x, y, pPainter->GetT()));
							break;
						case 7:
							x--;
							y++;
							if (IsInMap(x, y))
								cell.ChangeEnergy(Photosyntes(x, y, pPainter->GetT()));
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
									if (Cells[i].GetCoord().X == x && Cells[i].GetCoord().Y == y) {
										Cells[i].ChangeEnergy(-SIMULATION_COUNT_MEAT);
										cell.ChangeEnergy(SIMULATION_COUNT_MEAT);
										break;
									}
								}
							break;
						case 1:
							x++;
							y++;
							if (IsInMap(x, y))
								for (int i = 0;i < size;i++) {
									if (Cells[i].GetCoord().X == x && Cells[i].GetCoord().Y == y) {
										Cells[i].ChangeEnergy(-SIMULATION_COUNT_MEAT);
										cell.ChangeEnergy(SIMULATION_COUNT_MEAT);
										break;
									}
								}
							break;
						case 2:
							x++;
							if (IsInMap(x, y))
								for (int i = 0;i < size;i++) {
									if (Cells[i].GetCoord().X == x && Cells[i].GetCoord().Y == y) {
										Cells[i].ChangeEnergy(-SIMULATION_COUNT_MEAT);
										cell.ChangeEnergy(SIMULATION_COUNT_MEAT);
										break;
									}
								}
							break;
						case 3:
							x++;
							y--;
							if (IsInMap(x, y))
								for (int i = 0;i < size;i++) {
									if (Cells[i].GetCoord().X == x && Cells[i].GetCoord().Y == y) {
										Cells[i].ChangeEnergy(-SIMULATION_COUNT_MEAT);
										cell.ChangeEnergy(SIMULATION_COUNT_MEAT);
										break;
									}
								}
							break;
						case 4:
							y--;
							if (IsInMap(x, y))
								for (int i = 0;i < size;i++) {
									if (Cells[i].GetCoord().X == x && Cells[i].GetCoord().Y == y) {
										Cells[i].ChangeEnergy(-SIMULATION_COUNT_MEAT);
										cell.ChangeEnergy(SIMULATION_COUNT_MEAT);
										break;
									}
								}
							break;
						case 5:
							x--;
							y--;
							if (IsInMap(x, y))
								for (int i = 0;i < size;i++) {
									if (Cells[i].GetCoord().X == x && Cells[i].GetCoord().Y == y) {
										Cells[i].ChangeEnergy(-SIMULATION_COUNT_MEAT);
										cell.ChangeEnergy(SIMULATION_COUNT_MEAT);
										break;
									}
								}
							break;
						case 6:
							x--;
							if (IsInMap(x, y))
								for (int i = 0;i < size;i++) {
									if (Cells[i].GetCoord().X == x && Cells[i].GetCoord().Y == y) {
										Cells[i].ChangeEnergy(-SIMULATION_COUNT_MEAT);
										cell.ChangeEnergy(SIMULATION_COUNT_MEAT);
										break;
									}
								}
							break;
						case 7:
							x--;
							y++;
							if (IsInMap(x, y))
								for (int i = 0;i < size;i++) {
									if (Cells[i].GetCoord().X == x && Cells[i].GetCoord().Y == y) {
										Cells[i].ChangeEnergy(-SIMULATION_COUNT_MEAT);
										cell.ChangeEnergy(SIMULATION_COUNT_MEAT);
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
									cell.ChangeEnergy(SIMULATION_COUNT_MINERAL);
									pMap->SetMineralMap(x, y, -0.05);
								}
								break;
							}
						case 1:
							{
								x++;
								y++;
								if (IsInMap(x, y)) {
									cell.ChangeEnergy(SIMULATION_COUNT_MINERAL);
									pMap->SetMineralMap(x, y, -0.05);
								}
								break;
							}
						case 2:
							{
								x++;
								if (IsInMap(x, y)) {
									cell.ChangeEnergy(SIMULATION_COUNT_MINERAL);
									pMap->SetMineralMap(x, y, -0.05);
								}
								break;
							}
						case 3:
							{
								x++;
								y--;
								if (IsInMap(x, y)) {
									cell.ChangeEnergy(SIMULATION_COUNT_MINERAL);
									pMap->SetMineralMap(x, y, -0.05);
								}
								break;
							}
						case 4:
							{
								y--;
								if (IsInMap(x, y)) {
									cell.ChangeEnergy(SIMULATION_COUNT_MINERAL);
									pMap->SetMineralMap(x, y, -0.05);
								}
								break;
							}
						case 5:
							{
								x--;
								y--;
								if (IsInMap(x, y)) {
									cell.ChangeEnergy(SIMULATION_COUNT_MINERAL);
									pMap->SetMineralMap(x, y, -0.05);
								}
								break;
							}
						case 6:
							{
								x--;
								if (IsInMap(x, y)) {
									cell.ChangeEnergy(SIMULATION_COUNT_MINERAL);
									pMap->SetMineralMap(x, y, -0.05);
								}
								break;
							}
						case 7:
							{
								x--;
								y++;
								if (IsInMap(x, y)) {
									cell.ChangeEnergy(SIMULATION_COUNT_MINERAL);
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

		assert(x - cell.GetCoord().X + 1 < 3);
		assert(y - cell.GetCoord().Y + 1 < 3);
		assert(AR < 8);
		assert(0 <= AR);
		assert(CM < 8);
		assert(0 <= CM);
		cell.ChangeEnergy(-1);
	}
}

void Simulation::GeneRetarget() {
	for (int iter = Cells.size() - 1; iter > -1; iter--) {
		Cell& cell = Cells[iter];
		COORD& cord = Cells[iter].GetCoord();

		if (Cells[iter].GetEnergy() <= 0 || pMap->IsSea(cord.X, cord.Y, LS)) {


			for (int ii = -1;ii < 2;ii++) {
				for (int jj = -1;jj < 2;jj++) {

					if (IsInMap((cord.X + jj), (cord.Y + ii)) && (ii != 0 || jj != 0)) {
						pMap->SetMineralMap(cord.X + jj, cord.Y + ii, 0.1);
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
		pMap->SetVisibleMap(Cells[iter].GetCoord().X, Cells[iter].GetCoord().Y, true);
	}
	//Do();

	pPainter->Paint(*pMap, Cells, LS);
}
