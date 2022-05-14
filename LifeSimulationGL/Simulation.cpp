#include "Simulation.h"

Simulation::Simulation(int cnt) {
	RandomShort random;

	pPainter = new Painter();
	pMap = new Map();
	pMap->GenerateMap(random.Next());

	for (int i = 0;i < cnt;i++) {
		short x = random.Next(MAP_X);
		short y = random.Next(MAP_Y);

		while (pMap->GetVisibleMap(x, y)) {
			x = random.Next(MAP_X);
			y = random.Next(MAP_Y);
		}

		COORD S = { x,y };
		Cells.push_back(Cell(S));
		pMap->SetVisibleMap(S.X, S.Y, true);
	}
}

void Simulation::GeneSwitch() {
	for (list<Cell>::iterator iter = Cells.begin(); iter != Cells.end(); iter++) {

		if (!iter->IsWait())
			iter->SwitchCommand(1);
		else
			iter->Waitt();

	}
}

void Simulation::GeneAction() {
	uint16_t CMD;
	uint8_t CM;
	uint8_t AR;

	for (list<Cell>::iterator iter = Cells.begin(); iter != Cells.end(); iter++) {
		CMD = iter->GetCurrentCommand();
		
		CM = CMD % 0x100;
		AR = CMD / 0x100;

		switch (CM) {
		case Nothing:
			{
			iter->SetWait();
			}
			break;
		default:
			{
			COORD S = iter->GetCoord();
			S.X += (rand() % 3) - 1;
			S.Y+= (rand() % 3) - 1;

			iter->SetCoord(S.X, S.Y);
			}
			break;
		}

		iter->ChangeEnergy(-1);
	}
}

void Simulation::GeneRetarget() {
	for (list<Cell>::iterator iter = Cells.begin(); iter != Cells.end(); iter++) {

	}
}
