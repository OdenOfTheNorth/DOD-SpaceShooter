#pragma once
#include <iostream>

class Math
{
public:
	static int GetRandom(int randSeed /*GameData* gameData*/, int min, int max);
	static double lerp(double a, double b, double f) { return a + f * (b - a); }
};

