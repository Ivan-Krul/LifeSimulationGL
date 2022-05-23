#pragma once

#include <Windows.h>
#include <stdint.h>
#include "Random.h"
#include "Define.h"
#include <cassert>

enum Command : uint8_t {
	Nothing = 0,
	Divide = 1,
	Move = 2,
	Photosyn = 3,
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

	int cmd = 0; 
public:
	void Init(COORD coord) {
		cmd++;
		RandomInt rand;

		Coord = coord;

		IterGene = CELL_STARTED_NUM_GENE;
		Energy = CELL_STARTED_ENERGY + rand.Next(255);
		Wait = 0;

		Col[0] = rand.Next(128) + 64;
		Col[1] = rand.Next(128) + 64;
		Col[2] = rand.Next(128) + 64;

		for (int i = 0;i < CELL_COUNT_GENES;i++) {
			Gene[i] = rand.Next(8);
			Args[i] = rand.Next(8);
			assert(Gene[i] < 8);
			assert(Args[i] < 8);
		}

	}

	Cell& Init(Cell& cell, int H) {
		cmd++;
		cell.Energy /= 2;
		Energy = cell.Energy;

		IterGene = cell.IterGene;
		Coord = cell.Coord;
		Wait = 0;

		RandomFloat random;
		RandomByte ran;

		Col[0] = cell.GetColorRed();
		Col[1] = cell.GetColorGreen();
		Col[2] = cell.GetColorBlue();


		for(int i=0;i<3;i++)
			if (random.Next(1) < CELL_CHANCE_MUTATION)
				Col[i] += ran.Next(-5, 5);

		for (int i = 0;i < CELL_COUNT_GENES;i++) {
			Gene[i] = cell.Gene[i];
			Args[i] = cell.Args[i];
			
			if (random.Next(1.0) < CELL_CHANCE_MUTATION) {
				Gene[i] = ran.Next(8);
				Args[i] = ran.Next(8);
			}
			assert(Gene[i] < 8);
			assert(Args[i] < 8);
		}
		return cell;
	}

	uint8_t GetColorRed() {
		cmd++;
		return Col[0];
	}
	uint8_t GetColorGreen() {
		cmd++;
		return Col[1];
	}
	uint8_t GetColorBlue() {
		cmd++;
		return Col[2];
	}

	int GetGene(int I) {
		cmd++;
		return Gene[I % CELL_COUNT_GENES];
	}
	int GetArgs(int I) {
		cmd++;
		return Args[I % CELL_COUNT_GENES];
	}

	int GetArgument() {
		cmd++;
		assert(Args[IterGene] < 8);
		return Args[IterGene];
	}
	int GetGene() {
		cmd++;
		assert(Gene[IterGene] < 8); 
		return Gene[IterGene];
	}

	void SetEnergy(uint16_t energy) {
		cmd++;Energy = energy;
	}
	void ChangeEnergy(int16_t energy) {
		cmd++;Energy += energy;
	}
	uint16_t GetEnergy() {
		cmd++;
		return Energy;
	}

	COORD& GetCoord() {
		cmd++;
		return Coord;
	}

	void SwitchCommand(int8_t change) {
		cmd++;
		IterGene += change;
		IterGene %= CELL_COUNT_GENES;
	}

	void SetCoord(short x, short y) {
		cmd++;
		if (&Coord.X != nullptr && &Coord.Y != nullptr) {
			Coord.X = x;
			Coord.Y = y;
		}
	}
};
