#pragma once
#include <stdint.h>
#include "Random.h"
#include "Define.h"
#include <cassert>

enum command {
	Divide,
	Move,
	Photosyn,
	EatCell,
	Mineral
};
//-------------------------------------------------
template<typename T>
void copy(T* ptr, T* to_ptr, unsigned long long size) {
	for (unsigned long long i = 0;i < size;i++) {
		ptr[i] = to_ptr[i];
	}
}
//-------------------------------------------------
class celular
{
	private:
	command _gene[CELL_COUNT_GENES];
	char _args[CELL_COUNT_GENES];
	short _current = CELL_STARTED_NUM_GENE;
	short _energy = CELL_STARTED_ENERGY;
	unsigned char _color[3];
	//-------------------------------------------------
	public:
	short _pos[2];
	//-------------------------------------------------
	private:
	command convert_to_command(int num);
	void fill_gene_and_args(int num, RandomByte &ran);
	//-------------------------------------------------
	public:
	celular(short pos[2]);
	celular(celular& celula, int arg);
	//-------------------------------------------------
	void change_energy(short changes);
	short get_energy();
	
	unsigned char get_color(int num);
	command get_command();
	char get_argument();

	void set_cordinates(short x,short y);
	void switch_command(short change);
};

