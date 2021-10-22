#pragma once
#include <math.h>


struct  Vector2
{
public:
	Vector2(double xValue, double yValue);
	Vector2();
	~Vector2();

	double x;
	double y;

	static double Distance(Vector2 distanceFrom, Vector2 distanceTo);
	static double DistanceNotSquard(Vector2 distanceFrom, Vector2 distanceTo);
	static double Distance(double distanceFromX, double distanceFromY, double distanceToX, double distanceToY);
	static double Dot(Vector2 a, Vector2 b);
	static Vector2 Perpendicular(Vector2 vector, bool isClockwise);
	static Vector2 GetDirection(Vector2 from, Vector2 to);
	static Vector2 GetNormalizedDirection(Vector2 from, Vector2 to);
	static Vector2 Zero() { return Vector2(0, 0); }

	static Vector2 Clamp(Vector2 pos, Vector2 min, Vector2 max);
	static Vector2 Lerp(Vector2 from, Vector2 to, double f);

	static double AngleFromDirection(Vector2 direction);
	static Vector2 DirectionFromAngle(double angle);

	Vector2 Normalized();
	void Normalize();
	double Magnitude() { return sqrt(x * x + y * y); }

	Vector2 operator+(const Vector2);
	Vector2 operator-(const Vector2);
	Vector2 operator-();
	Vector2 operator*(const double);
	Vector2 operator/(const double);
	void operator+=(const Vector2& v);

private:
};