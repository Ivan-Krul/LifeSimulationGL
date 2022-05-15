#include "Simulation.h"

void Simulation::Init(int cnt) {
	RandomShort random;

	pPainter = new Painter();
	pMap = new Map();
	pMap->GenerateMap(random.Next());

	for (int i = 0;i < cnt;i++) {
		short x = random.Next(MAP_X);
		short y = random.Next(MAP_Y);

		while (!pMap->GetVisibleMap(x, y)) {
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
		if (IsInMap(S.X, S.Y)) {
			Cells[iter].SetCoord(S.X, S.Y);
		}

		Cells[iter].ChangeEnergy(-1);
	}
}

void Simulation::GeneRetarget() {
	for (int iter = Cells.size()-1; iter>-1; iter--) {
		if (Cells[iter].GetEnergy() <= 0) {
			//for (int ii = -1;ii < 2;ii++) {
			//	for (int jj = -1;jj < 2;jj++) {

			//		if (IsInMap((Cells[iter].GetCoord().X + jj), (Cells[iter].GetCoord().Y + ii)) && ii+jj!=0) {
			//			pMap->SetMineralMap(Cells[iter].GetCoord().X + jj, Cells[iter].GetCoord().Y + ii, 5);
			//		}

			//	}
			//}

			Cells.erase(Cells.begin()+iter);
		}
	}
}

void Simulation::Do()
{
	for (int iter = Cells.size() - 1; iter > -1; iter--) {
		if (Cells[iter].GetEnergy() <= 0) {
			Cells.erase(Cells.begin() + iter);
			continue;
		}

		if (!Cells[iter].IsWait())
			Cells[iter].SwitchCommand(1);
		else
			Cells[iter].Waitt();

		uint16_t CMD= Cells[iter].GetCurrentCommand();
		uint8_t CM = CMD % 0x100;
		uint8_t AR = CMD / 0x100;

		COORD S = Cells[iter].GetCoord();
		S.X += (rand() % 3) - 1;
		S.Y += (rand() % 3) - 1;
		if (IsInMap(S.X, S.Y)) {
			Cells[iter].SetCoord(S.X, S.Y);
		}

		Cells[iter].ChangeEnergy(-1);

		pMap->SetVisibleMap(Cells[iter].GetCoord().X, Cells[iter].GetCoord().Y, true);
	}
}

void Simulation::Paint() {
	float a = sinf(pPainter->GetT()*0.01)*0.1+0.5;
	for (int i = 0;i < MAP_X;i++)
		for (int j = 0;j < MAP_Y;j++)
			pMap->SetVisibleMap(i, j, false);

	Do();

	pPainter->Paint(*pMap,Cells, a);
}
