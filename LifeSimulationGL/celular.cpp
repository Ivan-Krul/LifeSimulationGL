#include "celular.h"

command celular::convert_to_command(int num) {
	switch (num) {
		case 0:return Divide;
		case 1:return Move; 
		case 2:return Photosyn; 
		case 3:return EatCell; 
		case 4:return Mineral; 
	}
}
//-------------------------------------------------
void celular::fill_gene_and_args(int num, RandomByte& ran) {
	_gene[num] = convert_to_command(ran.Next(5));
	_args[num] = ran.Next(8);
}
//-------------------------------------------------
celular::celular(short pos[2]) {
	copy(_pos, pos, 2);
	RandomByte ran;

	for (int i = 0;i < 3;i++) {
		_color[i] = ran.Next(128, 255);
	}
	for (short i = 0;i < CELL_COUNT_GENES;i++) {
		fill_gene_and_args(i, ran);
	}
}
//-------------------------------------------------
void celular::change_energy(short changes) {
	_energy += changes;
}
short celular::get_energy() {
	return _energy;
}
command celular::get_command() {
	return _gene[_current];
}
char celular::get_argument() {
	return _args[_current];
}
unsigned char celular::get_color(int num) {
	return _color[num];
}
void celular::switch_command(short change) {
	_current += change;
	_current %= CELL_COUNT_GENES;
}
void celular::set_cordinates(short x, short y) {
	_pos[0] = x;
	_pos[1] = y;
}
//-------------------------------------------------
celular::celular(celular& celula, int arg) {
	RandomFloat ran;
	RandomByte ranran;

	celula._energy /= 2;
	_energy = celula._energy;
	copy(_pos, celula._pos, 2);
	for (int i = 0;i < 3;i++) {
		_color[i] = celula._color[i];
		if (ran.Next(1.0) > CELL_CHANCE_MUTATION)
			_color[i] = ranran.Next(-5, 5);
	}
	for (int i = 0;i < CELL_COUNT_GENES;i++) {
		_gene[i] = celula._gene[i];
		_args[i] = celula._args[i];
		if (ran.Next(1.0) > CELL_CHANCE_MUTATION) {
			fill_gene_and_args(i, ranran);
		}
	}
}
