#include "Vector2.h"
#include <stdlib.h>
#include <iostream>
#include "Math.h"


Vector2::Vector2(double xValue = 0, double yValue = 0)
{
	x = xValue;
	y = yValue;
}
Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::~Vector2()
{
}

Vector2 Vector2::Clamp(Vector2 pos, Vector2 min, Vector2 max)
{
	if (pos.x > max.x)
	{
		pos.x = max.x;
	}
	else if (pos.x < min.x)
	{
		pos.x = min.x;
	}

	if (pos.y > max.y)
	{
		pos.y = max.y;
	}
	else if (pos.y < min.y)
	{
		pos.y = min.y;
	}
	return pos;
}

double Vector2::AngleFromDirection(Vector2 direction)
{
	return atan2(direction.y, direction.x);
}

Vector2 Vector2::DirectionFromAngle(double angle)
{
	Vector2 dir = Vector2(0, 0);

	dir.x = cos(angle);
	dir.y = sin(angle);

	return dir;
}

Vector2 Vector2::Normalized()
{
	double magn = Magnitude();
	return Vector2(x / magn, y / magn);
}

double Vector2::Distance(Vector2 distanceFrom, Vector2 distanceTo)
{
	return Distance(distanceFrom.x, distanceFrom.y, distanceTo.x, distanceTo.y);
}

double Vector2::DistanceNotSquard(Vector2 distanceFrom, Vector2 distanceTo)
{
	double power = pow(distanceFrom.x - distanceTo.x, 2) + pow(distanceFrom.y - distanceTo.y, 2) * 1.0;

	return power;
}

double Vector2::Distance(double distanceFromX, double distanceFromY, double distanceToX, double distanceToY)
{
	double power = pow(distanceFromX - distanceToX, 2) + pow(distanceFromY - distanceToY, 2) * 1.0;

	return sqrt(power);
}

double Vector2::Dot(Vector2 a, Vector2 b)
{
	return a.x * b.x + a.y * b.y;
}

Vector2 Vector2::Perpendicular(Vector2 vector, bool isClockwise)
{
	if (isClockwise)
	{
		return Vector2(vector.y, -vector.x);

	}
	else
	{
		return Vector2(-vector.y, vector.x);
	}
}

Vector2 Vector2::GetDirection(Vector2 from, Vector2 to)
{
	return to - from;
}

Vector2 Vector2::GetNormalizedDirection(Vector2 from, Vector2 to)
{
	return (to - from).Normalized();
}

void Vector2::Normalize()
{
	Vector2 normalizedVector = Normalized();
	x = normalizedVector.x;
	y = normalizedVector.y;
}

Vector2 Vector2::operator+(const Vector2 v)
{
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2 v)
{
	return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator-()
{
	return Vector2(0 - x, 0 - y);
}

Vector2 Vector2::operator*(const double d)
{
	return Vector2(x * d, y * d);
}

Vector2 Vector2::operator/(const double d)
{
	return Vector2(x / d, y / d);
}

void Vector2::operator+=(const Vector2& v)
{
	this->x += v.x;
	this->y += v.y;
}

Vector2 Vector2::Lerp(Vector2 from, Vector2 to, double f)
{
	return Vector2(Math::lerp(from.x, to.x, f), Math::lerp(from.y, to.y, f));
}



