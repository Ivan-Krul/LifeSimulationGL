#pragma once
#include <ctime>
#include <cmath>

static unsigned long long GlobalSeed = time(NULL);

class RandomLongLong {
	typedef unsigned long long RandVar;

	RandVar X;
	RandVar a;
	RandVar c;
	RandVar seed;
	size_t iter;

public:
	RandomLongLong() {
		seed = GlobalSeed;

		Restart();
	}

	RandomLongLong(RandVar seed) {
		this->seed = seed;

		Restart();
	}

	void ChangeSeed(RandVar seed) {
		this->seed = seed;

		Restart();
	}

	RandVar GetSeed() {
		return seed;
	}

	size_t GetIteration() {
		return iter;
	}

	void ChangeRules(RandVar a, RandVar c) {
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

	RandVar Next() {
		X = X * a + c;
		iter++;
		return X;
	}

	RandVar Next(RandVar board) {
		X = X * a + c;
		iter++;
		return X % board;
	}

	RandVar Next(RandVar left, RandVar rigth) {
		X = X * a + c;
		iter++;
		return (X % (rigth - left)) + left;
	}
};

class RandomInt {
	typedef unsigned int RandVar;

	RandVar X;
	RandVar a;
	RandVar c;
	RandVar seed;
	size_t iter;

public:
	RandomInt() {
		seed = GlobalSeed;

		Restart();
	}

	RandomInt(RandVar seed) {
		this->seed = seed;

		Restart();
	}

	void ChangeSeed(RandVar seed) {
		this->seed = seed;

		Restart();
	}

	RandVar GetSeed() {
		return seed;
	}

	size_t GetIteration() {
		return iter;
	}

	void ChangeRules(RandVar a, RandVar c) {
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

	RandVar Next() {
		X = X * a + c;
		iter++;
		return X;
	}

	RandVar Next(RandVar board) {
		X = X * a + c;
		iter++;
		return X % board;
	}

	RandVar Next(RandVar left, RandVar rigth) {
		X = X * a + c;
		iter++;
		return (X % (rigth-left))+left;
	}
};

class RandomShort {
	typedef unsigned short RandVar;

	RandVar X;
	RandVar a;
	RandVar c;
	RandVar seed;
	size_t iter;

public:
	RandomShort() {
		seed = GlobalSeed;

		Restart();
	}

	RandomShort(RandVar seed) {
		this->seed = seed;

		Restart();
	}

	void ChangeSeed(RandVar seed) {
		this->seed = seed;

		Restart();
	}

	RandVar GetSeed() {
		return seed;
	}

	size_t GetIteration() {
		return iter;
	}

	void ChangeRules(RandVar a, RandVar c) {
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

	RandVar Next() {
		X = X * a + c;
		iter++;
		return X;
	}

	RandVar Next(RandVar board) {
		X = X * a + c;
		iter++;
		return X % board;
	}

	RandVar Next(RandVar left, RandVar rigth) {
		X = X * a + c;
		iter++;
		return (X % (rigth - left)) + left;
	}
};

class RandomByte {
	typedef unsigned char RandVar;

	RandVar X;
	RandVar a;
	RandVar c;
	RandVar seed;
	size_t iter;

public:
	RandomByte() {
		seed = GlobalSeed;

		Restart();
	}

	RandomByte(RandVar seed) {
		this->seed = seed;

		Restart();
	}

	void ChangeSeed(RandVar seed) {
		this->seed = seed;

		Restart();
	}

	RandVar GetSeed() {
		return seed;
	}

	size_t GetIteration() {
		return iter;
	}

	void ChangeRules(RandVar a, RandVar c) {
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

	RandVar Next() {
		X = X * a + c;
		iter++;
		return X;
	}

	RandVar Next(RandVar board) {
		X = X * a + c;
		iter++;
		return X % board;
	}

	RandVar Next(RandVar left, RandVar rigth) {
		X = X * a + c;
		iter++;
		return (X % (rigth - left)) + left;
	}
};

class RandomFloat {
	typedef unsigned int RandVar;

	RandVar X;
	RandVar a;
	RandVar c;
	RandVar seed;
	size_t iter;

public:
	RandomFloat() {
		seed = GlobalSeed;

		Restart();
	}

	RandomFloat(RandVar seed) {
		this->seed = seed;

		Restart();
	}

	void ChangeSeed(RandVar seed) {
		this->seed = seed;

		Restart();
	}

	RandVar GetSeed() {
		return seed;
	}

	size_t GetIteration() {
		return iter;
	}

	void ChangeRules(RandVar a, RandVar c) {
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
		X = X * a + c ;
		iter++;
		return float(X) / 0x7fff;
	}

	float Next(float board) {
		X = X * a + c;
		iter++;
		return std::fmod(float(X)/0x7fff,board);
	}

	float Next(float left, float rigth) {
		X = X * a + c;
		iter++;
		return std::fmod(float(X) / 0x7fff, rigth-left) + left;
	}
};

class RandomDouble {
	typedef unsigned int RandVar;

	RandVar X;
	RandVar a;
	RandVar c;
	RandVar seed;
	size_t iter;

public:
	RandomDouble() {
		seed = GlobalSeed;

		Restart();
	}

	RandomDouble(RandVar seed) {
		this->seed = seed;

		Restart();
	}

	void ChangeSeed(RandVar seed) {
		this->seed = seed;

		Restart();
	}

	RandVar GetSeed() {
		return seed;
	}

	size_t GetIteration() {
		return iter;
	}

	void ChangeRules(RandVar a, RandVar c) {
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
