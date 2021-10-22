#pragma once
#include "SDL.h"
//#include <SDL_image.h>
//#include <SDL_TTF.h>
//#include "Player.h"
//#include "Enemy.h"
//#include <vector>

/*
struct Vector2
{
public:
	Vector2(double xValue = 0, double yValue = 0) {
		x = xValue;
		y = yValue;
	}
	/*Vector2() {x = 0;	y = 0;}

	double x;
	double y;
};
struct VectorMath
{
public:
	static Vector2 AddVectors(Vector2 current, Vector2 ToAdd) {
		Vector2 tempVec;
		tempVec.x = current.x + ToAdd.x;
		tempVec.y = current.y + ToAdd.y;

		return tempVec;// Vector2(current.x + ToAdd.x, current.y + ToAdd.y);
	}

	static Vector2 SubtractVectors(Vector2 current, Vector2 ToSubtract) {
		Vector2 tempVec;
		tempVec.x = current.x - ToSubtract.x;
		tempVec.y = current.y - ToSubtract.y;

		return tempVec;// Vector2(current.x - ToSubtract.x, current.y - ToSubtract.y);
	}

	static Vector2 MultiplayVectors(Vector2 current, double ToMultiplay) {
		Vector2 tempVec;
		tempVec.x = current.x * ToMultiplay;
		tempVec.y = current.y * ToMultiplay;

		return tempVec;// Vector2(current.x * ToMultiplay, current.y * ToMultiplay);
	}

	static Vector2 ClampVectors(Vector2 current, Vector2 min, Vector2 max) {

		if (current.x > max.x)		{	//current bigger then max
			current.x = max.x;		}

		if (current.y > max.y)		{	//current bigger then max
			current.y = max.y;		}

		if (current.x < min.x)		{	//current Lower then min
			current.x = min.x;		}

		if (current.y < min.y)		{	//current Lower then min
			current.y = min.y;		}

		return current;
	}

	static Vector2 NormalizedVector(Vector2 current) {

		double magnetude = sqrt(current.x * current.x + current.y * current.y);
		double x = magnetude / (current.x * current.x);
		double y = magnetude / (current.y * current.y);

		return Vector2(x, y);
	}
};
*/



