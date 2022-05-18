#include "Simulation.h"

void Simulation::Init(int cnt) {
	RandomShort random;

	pPainter = new Painter();
	pMap = new Map();
	pMap->GenerateMap();

	for (int i = 0;i < cnt;i++) {
		short x = random.Next(MAP_X);
		short y = random.Next(MAP_Y);

		while (!pMap->GetVisibleMap(x, y) || pMap->IsSea(x,y,LS)) {
			x = random.Next(MAP_X);
			y = random.Next(MAP_Y);
		}

		COORD S = { x,y };
		Cells.push_back(Cell());
		Cells[Cells.size() - 1].Init(S);
	}
}

void Simulation::GeneSwitch() {
	for (int iter = 0; iter != Cells.size(); iter++) {

		if (!Cells[iter].IsWait())
			Cells[iter].SwitchCommand(1);
		else
			Cells[iter].Waitt();

	}
}

void Simulation::GeneAction() {
	uint16_t CMD;
	uint8_t CM;
	uint8_t AR;

	for (int iter = 0; iter != Cells.size(); iter++) {
		CMD = Cells[iter].GetCurrentCommand();
		
		CM = CMD % 0x100;
		AR = CMD / 0x100;

		//switch (CM) {
		//case Nothing:
		//	{
		//	iter->SetWait();
		//	}
		//	break;
		//default:
		//	{
		//	COORD S = iter->GetCoord();
		//	S.X += (rand() % 3) - 1;
		//	S.Y+= (rand() % 3) - 1;

		//	iter->SetCoord(S.X, S.Y);
		//	}
		//	break;
		//}

		COORD S = Cells[iter].GetCoord();
		S.X += (rand() % 3) - 1;
		S.Y+= (rand() % 3) - 1;
		if (IsInMap(S.X, S.Y) && !pMap->IsSea(S.X,S.Y,LS)) {
			Cells[iter].SetCoord(S.X, S.Y);
			pMap->SetMineralMap(S.X, S.Y, -0.01);
		}

		

		Cells[iter].ChangeEnergy(-1);
	}
}

void Simulation::GeneRetarget() {
	for (int iter = Cells.size()-1; iter>-1; iter--) {
		Cell& cell = Cells[iter];
		COORD& cord = Cells[iter].GetCoord();

		if (Cells[iter].GetEnergy() <= 0 || pMap->IsSea(cord.X, cord.Y, LS)) {


			for (int ii = -1;ii < 2;ii++) {
				for (int jj = -1;jj < 2;jj++) {

					if (IsInMap((cord.X + jj), (cord.Y + ii)) && (ii!=0||jj!=0)) {
						pMap->SetMineralMap(cord.X + jj, cord.Y + ii, 0.1);
					}

				}
			}

			Cells.erase(Cells.begin()+iter);
		}
	}
}

void Simulation::Paint() {
	LS = sinf(pPainter->GetT()*0.01)*0.1+ BiasLS;
	for (int i = 0;i < MAP_X;i++)
		for (int j = 0;j < MAP_Y;j++)
			pMap->SetVisibleMap(i, j, false);

	for (int iter = Cells.size() - 1; iter > -1; iter--) {
		pMap->SetVisibleMap(Cells[iter].GetCoord().X, Cells[iter].GetCoord().Y, true);
	}
	//Do();

	pPainter->Paint(*pMap,Cells, LS);
}
