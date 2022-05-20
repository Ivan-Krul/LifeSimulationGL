#pragma once

#include <Windows.h>
#include <stdint.h>
#include "Random.h"
#include "Define.h"

enum Command : uint8_t {
	Nothing = 0,
	Divide = 1,
	Move = 2,
	Photosyn = 3,
	EatPlant = 4,
	EatCell = 5,
	Mineral = 6,
	Link = 7
};

class Cell {
	COORD Coord;
	uint8_t Gene[CELL_COUNT_GENES];
	uint8_t Args[CELL_COUNT_GENES];
	uint8_t	IterGene;
	uint8_t Wait;
	uint16_t Energy = 1;
	uint8_t Col[3];
public:
	void Init(COORD coord) {
		RandomByte rand;

		Coord = coord;

		IterGene = CELL_STARTED_NUM_GENE;
		Energy = CELL_STARTED_ENERGY + rand.Next(255);
		Wait = 0;

		Col[0] = rand.Next(128) + 64;
		Col[1] = rand.Next(128) + 64;
		Col[2] = rand.Next(128) + 64;

		for (int i = 0;i < CELL_COUNT_GENES;i++) {
			Gene[i] = rand.Next(3);
			Args[i] = rand.Next(8);
		}
	}

	void Init(Cell& cell, int H) {
		cell.SetEnergy(cell.GetEnergy() / 2);
		Energy = cell.GetEnergy();

		IterGene = cell.IterGene;
		Coord = cell.GetCoord();

		RandomFloat random;
		RandomByte ran;

		Col[0] = cell.GetColorRed();
		Col[1] = cell.GetColorGreen();
		Col[2] = cell.GetColorBlue();


		for(int i=0;i<3;i++)
			if (random.Next(1) < CELL_CHANCE_MUTATION)
				Col[i] += ran.Next(-5, 5);

		for (int i = 0;i < CELL_COUNT_GENES;i++) {
			Gene[i] = cell.GetGene(i);
			Args[i] = cell.GetArgs(i);
			
			if (random.Next(1) < CELL_CHANCE_MUTATION) {
				Gene[i] = ran.Next(3);
				Args[i] = ran.Next(8);
			}
		}
	}

	uint8_t GetColorRed() { return Col[0]; }
	uint8_t GetColorGreen() { return Col[1]; }
	uint8_t GetColorBlue() { return Col[2]; }

	uint8_t GetGene(int I) { return Gene[I % CELL_COUNT_GENES]; }
	uint8_t GetArgs(int I) { return Args[I % CELL_COUNT_GENES]; }

	uint8_t GetArgument() { return Args[IterGene]; }
	uint8_t GetCommand() { return Gene[IterGene]; }

	void SetEnergy(uint16_t energy) { Energy = energy; }
	void ChangeEnergy(int16_t energy) { Energy += energy; }
	uint16_t GetEnergy() { return Energy; }

	COORD& GetCoord() { return Coord; }

	void SwitchCommand(int8_t change) {
		IterGene += change;
		IterGene %= CELL_COUNT_GENES;
	}

	void SetCoord(short x, short y) {
		if (&Coord.X != nullptr && &Coord.Y != nullptr) {
			Coord.X = x;
			Coord.Y = y;
		}
	}
};
