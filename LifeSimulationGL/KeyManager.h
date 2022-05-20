#pragma once
#include "Define.h"
#include <Windows.h>
#include <map>

using std::map;
using std::pair;

class KeyManeger {
	map<short, int> keys;
	public:

	void InsertKey(int vKeys) {
		pair<short, int> key;
		key.first = keys.size();
		key.second = vKeys;
		keys.insert(key);
	}

	bool Feel(short ind) {
		map<short, int>::iterator iter = keys.find(ind);
		return GetAsyncKeyState(iter->second);
	}

	short Size() {
		return keys.size();
	}
};
