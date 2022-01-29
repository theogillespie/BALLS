#pragma once

#include <LinearMath/btVector3.h>
#include <string>
#include <cstdio>

using namespace std;

string vecToString(btVector3* v) {
	char buffer[100]; // there is probably a better way...
	sprintf(buffer, "x: %F, y: %F, z: %F", v->getX(), v->getY(), v->getZ());
	return buffer;
}

btVector3 vecZero() {
	return btVector3(0, 0, 0);
}