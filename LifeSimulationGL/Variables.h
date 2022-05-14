#pragma once

template<typename T>
struct Point4 {
	T X, Y, Z, W;
};

template<typename T>
struct Point3 {
	T X, Y, Z;
};

template<typename T>
struct Point2 {
	T X, Y;
};

bool IsInMap(int x, int y) {
	return (0 <= x) && (x < MAP_X) && (0 <= y) && (y < MAP_Y);
}
