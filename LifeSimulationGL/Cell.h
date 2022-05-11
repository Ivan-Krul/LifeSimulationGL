#pragma once

#include <Windows.h>
#include <stdint.h>

#define CELL_COUNT_GENES 4
#define CELL_CHANCE_MUTATION 0.2f

class Cell {
	COORD Coord;
	uint8_t Gene[CELL_COUNT_GENES];
	uint8_t	IterGene;

	Cell(COORD coord) {
		Coord = coord;
		for (int i = 0;i < CELL_COUNT_GENES;i++) {
			Gene[CELL_COUNT_GENES];
		}
	}
};
