#pragma once
#include <ctime>
#include <cmath>

static class GlobalRandom {
	unsigned long long X;
	unsigned long long a;
	unsigned long long c;
	unsigned long long seed;
	public:
	GlobalRandom() {
		Init();
	}

	void Init() {
		seed = time(NULL);
		X = seed;
		a = 214013;
		c = 2531011;
	}
	void Init(unsigned long long Seed) {
		seed = Seed;
		X = seed;
		a = 214013;
		c = 2531011;
	}

	unsigned long long GiveSeed() {
		X = X * a + c;
		return X;
	}
};

static GlobalRandom global;

class RandomLongLong {
	unsigned long long X;
	unsigned long long a;
	unsigned long long c;
	unsigned long long seed;
	size_t iter;

	public:
	RandomLongLong() {
		seed = global.GiveSeed();

		Restart();
	}

	RandomLongLong(unsigned long long seed) {
		this->seed = seed;

		Restart();
	}

	void ChangeSeed(unsigned long long seed) {
		this->seed = seed;

		Restart();
	}

	unsigned long long GetSeed() {
		return seed;
	}

	size_t GetIteration() {
		return iter;
	}

	void ChangeRules(unsigned long long a, unsigned long long c) {
		this->a = a;
		this->c = c;
		X = seed;
		iter = 0;
	}

	void Restart() {
		iter = 0;

		X = seed;
		a = 214013;
		c = 2531011;
	}

	unsigned long long Next() {
		X = X * a + c;
		iter++;
		return X;
	}

	unsigned long long Next(unsigned long long board) {
		X = X * a + c;
		iter++;
		return X % board;
	}

	unsigned long long Next(unsigned long long left, unsigned long long rigth) {
		X = X * a + c;
		iter++;
		return (X % (rigth - left)) + left;
	}
};

class RandomInt {
	unsigned int X;
	unsigned int a;
	unsigned int c;
	unsigned int seed;
	size_t iter;

	public:
	RandomInt() {
		seed = global.GiveSeed();

		Restart();
	}

	RandomInt(unsigned int seed) {
		this->seed = seed;

		Restart();
	}

	void ChangeSeed(unsigned int seed) {
		this->seed = seed;

		Restart();
	}

	unsigned int GetSeed() {
		return seed;
	}

	size_t GetIteration() {
		return iter;
	}

	void ChangeRules(unsigned int a, unsigned int c) {
		this->a = a;
		this->c = c;
		X = seed;
		iter = 0;
	}

	void Restart() {
		iter = 0;

		X = seed;
		a = 214013;
		c = 2531011;
	}

	unsigned int Next() {
		X = X * a + c;
		iter++;
		return X;
	}

	unsigned int Next(unsigned int board) {
		X = X * a + c;
		iter++;
		return X % board;
	}

	unsigned int Next(unsigned int left, unsigned int rigth) {
		X = X * a + c;
		iter++;
		return (X % (rigth - left)) + left;
	}
};

class RandomShort {
	typedef unsigned short RandVar;

	unsigned short X;
	unsigned short a;
	unsigned short c;
	unsigned short seed;
	size_t iter;

	public:
	RandomShort() {
		seed = global.GiveSeed();

		Restart();
	}

	RandomShort(unsigned short seed) {
		this->seed = seed;

		Restart();
	}

	void ChangeSeed(unsigned short seed) {
		this->seed = seed;

		Restart();
	}

	unsigned short GetSeed() {
		return seed;
	}

	size_t GetIteration() {
		return iter;
	}

	void ChangeRules(unsigned short a, unsigned short c) {
		this->a = a;
		this->c = c;
		X = seed;
		iter = 0;
	}

	void Restart() {
		iter = 0;

		X = seed;
		a = 214013;
		c = 2531011;
	}

	unsigned short Next() {
		X = X * a + c;
		iter++;
		return X;
	}

	unsigned short Next(unsigned short board) {
		X = X * a + c;
		iter++;
		return X % board;
	}

	unsigned short Next(unsigned short left, unsigned short rigth) {
		X = X * a + c;
		iter++;
		return (X % (rigth - left)) + left;
	}
};

class RandomByte {
	unsigned char X;
	unsigned char a;
	unsigned char c;
	unsigned char seed;
	size_t iter;

	public:
	RandomByte() {
		seed = global.GiveSeed();

		Restart();
	}

	RandomByte(unsigned char seed) {
		this->seed = seed;

		Restart();
	}

	void ChangeSeed(unsigned char seed) {
		this->seed = seed;

		Restart();
	}

	unsigned char GetSeed() {
		return seed;
	}

	size_t GetIteration() {
		return iter;
	}

	void ChangeRules(unsigned char a, unsigned char c) {
		this->a = a;
		this->c = c;
		X = seed;
		iter = 0;
	}

	void Restart() {
		iter = 0;

		X = seed;
		a = 214013;
		c = 2531011;
	}

	unsigned char Next() {
		X = X * a + c;
		iter++;
		return X;
	}

	unsigned char Next(unsigned char board) {
		X = X * a + c;
		iter++;
		return X % board;
	}

	unsigned char Next(unsigned char left, unsigned char rigth) {
		X = X * a + c;
		iter++;
		return (X % (rigth - left)) + left;
	}
};

class RandomFloat {
	unsigned int X;
	unsigned int a;
	unsigned int c;
	unsigned int seed;
	size_t iter;

	public:
	RandomFloat() {
		seed = global.GiveSeed();

		Restart();
	}

	RandomFloat(unsigned int seed) {
		this->seed = seed;

		Restart();
	}

	void ChangeSeed(unsigned int seed) {
		this->seed = seed;

		Restart();
	}

	unsigned int GetSeed() {
		return seed;
	}

	size_t GetIteration() {
		return iter;
	}

	void ChangeRules(unsigned int a, unsigned int c) {
		this->a = a;
		this->c = c;
		X = seed;
		iter = 0;
	}

	void Restart() {
		iter = 0;

		X = seed;
		a = 214013;
		c = 2531011;
	}

	float Next() {
		X = X * a + c;
		iter++;
		return float(X) / 0x7fff;
	}

	float Next(float board) {
		X = X * a + c;
		iter++;
		return std::fmod(float(X) / 0x7fff, board);
	}

	float Next(float left, float rigth) {
		X = X * a + c;
		iter++;
		return std::fmod(float(X) / 0x7fff, rigth - left) + left;
	}
};

class RandomDouble {
	unsigned int X;
	unsigned int a;
	unsigned int c;
	unsigned int seed;
	size_t iter;

	public:
	RandomDouble() {
		seed = global.GiveSeed();

		Restart();
	}

	RandomDouble(unsigned int seed) {
		this->seed = seed;

		Restart();
	}

	void ChangeSeed(unsigned int seed) {
		this->seed = seed;

		Restart();
	}

	unsigned int GetSeed() {
		return seed;
	}

	size_t GetIteration() {
		return iter;
	}

	void ChangeRules(unsigned int a, unsigned int c) {
		this->a = a;
		this->c = c;
		X = seed;
		iter = 0;
	}

	void Restart() {
		iter = 0;

		X = seed;
		a = 214013;
		c = 2531011;
	}

	double Next() {
		X = X * a + c;
		iter++;
		return double(X) / 0x7fff;
	}

	double Next(double board) {
		X = X * a + c;
		iter++;
		return std::fmod(double(X) / 0x7fff, board);
	}

	double Next(double left, double rigth) {
		X = X * a + c;
		iter++;
		return std::fmod(double(X) / 0x7fff, rigth - left) + left;
	}
};
