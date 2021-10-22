#include "Math.h"


int Math::GetRandom(int randSeed, int min, int max) {
	randSeed++;
	randSeed *= 13;
	//srand((int) time(NULL) + randSeed);

	return rand() % (max - min) + min;
}