#pragma once

#include <Windows.h>
#include <stdint.h>
#include "Random.h"

#define CELL_COUNT_GENES 4
#define CELL_CHANCE_MUTATION 0.2f
#define CELL_STARED_ENERGY 20
#define CELL_STARTED_NUM_GENE 0

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
	uint8_t Gene[CELL_COUNT_GENES*2];
	uint8_t	IterGene;
	uint8_t Wait;
	uint16_t Energy;
public:
	Cell(COORD coord) {
		Coord = coord;

		IterGene = CELL_STARTED_NUM_GENE;
		Energy = CELL_STARED_ENERGY;
		Wait = 0;

		RandomByte rand;

		for (int i = 0;i < CELL_COUNT_GENES*2;i++) {
			if (i % 2 == 0) Gene[i] = rand.Next(8);
			else if (Gene[i - 1] == Nothing) Gene[i] = rand.Next(16);
			else Gene[i] = rand.Next(8);
		}
	}

	Cell(Cell& cell) {
		Energy = cell.GetEnergy() / 2;
		cell.SetEnergy(cell.GetEnergy() / 2);

		IterGene = cell.IterGene;

		RandomFloat random;
		RandomInt ran(random.Next());

		for (int i = 0;i < CELL_COUNT_GENES * 2;i++) {
			Gene[i] = cell.GetGene(i);

			if (random.Next(1) < CELL_CHANCE_MUTATION) {
				
				Gene[i] += ran.Next(-1, 1);
			}
		}
	}

	uint8_t GetGene(int I) {
		return Gene[I % (CELL_COUNT_GENES * 2)];
	}

	void SetEnergy(uint16_t energy) {
		Energy = energy;
	}

	uint16_t GetEnergy() {
		return Energy;
	}

	COORD GetCoord() {
		return Coord;
	}
};