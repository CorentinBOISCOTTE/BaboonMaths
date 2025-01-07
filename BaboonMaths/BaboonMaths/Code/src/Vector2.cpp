#include "BaboonMaths.h"

Vector2::Vector2() : x(0.f), y(0.f) {}

Vector2::Vector2(float _x, float _y) : x(_x), y(_y) {}

Vector2::Vector2(float coords) : x(coords), y(coords) {}

void Vector2::Print()
{
	std::cout << "Vector2 : " << "x = " << x << ", y = " << y << std::endl;
}

void Vector2::BlankPrint()
{
	std::cout << x << "  " << y << std::endl;
}

void Vector2::Opposite()
{
	x *= -1.f;
	y *= -1.f;
}

void Vector2::Invert()
{
	x = 1 / x;
	y = 1 / y;
}

void Vector2::AddNumber(float number)
{
	x += number;
	y += number;
}

void Vector2::MultiplyNumber(float number)
{
	x *= number;
	y *= number;
}

float Vector2::operator[](int index)
{
	if (index < 0 || index > 1)
	{
		std::cout << "Error : overflow" << std::endl;
		return NULL;
	}

	if (index == 0)
		return x;
	else if (index == 1)
		return y;
}

Vector2 Vector2::Add(Vector2 v1, Vector2 v2)
{
	Vector2 v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;

	return v;
}

Vector2 Vector2::Multiply(Vector2 v1, Vector2 v2)
{
	Vector2 v;

	v.x = v1.x * v2.x;
	v.y = v1.y * v2.y;

	return v;
}

Vector2 Vector2::MidPoint(Vector2 v1, Vector2 v2)
{
	Vector2 v3;

	v3.x = (v1.x + v2.x) / 2;
	v3.y = (v1.y + v2.y) / 2;

	return v3;
}

float Vector2::Distance(Vector2 p1, Vector2 p2)
{
	float xSquared = powf(p1.x - p2.x, 2.f);
	float ySquared = powf(p1.y - p2.y, 2.f);
	float dist = sqrtf(xSquared + ySquared);

	return dist;
}

float Vector2::SquaredNorm(Vector2 v)
{
	float xSquared = powf(v.x, 2.f);
	float ySquared = powf(v.y, 2.f);
	float squaredNorm = xSquared + ySquared;

	return squaredNorm;
}

float Vector2::Norm(Vector2 v)
{
	float norm = sqrtf(Vector2::SquaredNorm(v));

	return norm;
}

Vector2 Vector2::Normalize(Vector2 v)
{
	float norm = Vector2::Norm(v);

	return { v.x / norm, v.y / norm };
}

float Vector2::DotProduct(Vector2 v1, Vector2 v2)
{
	float dotProduct = (v1.x * v2.x) + (v1.y * v2.y);

	return dotProduct;
}

float Vector2::CrossProduct(Vector2 v1, Vector2 v2)
{
	float crossProduct = (v1.x * v2.y) - (v2.x * v1.y);

	return crossProduct;
}

float Vector2::GetAngle(Vector2 v1, Vector2 v2)
{
	float dotProduct = Vector2::DotProduct(v1, v2);
	float v1Norm = Vector2::Norm(v1);
	float v2Norm = Vector2::Norm(v2);

	if ((v1Norm * v2Norm) <= 0.0f)
		return 0.0f;

	float angle = acosf(dotProduct / (v1Norm * v2Norm));

	return angle;
}

Vector2 Vector2::Rotate(Vector2 p, float theta, Vector2 anchor)
{
	Vector2 pTemp = p - anchor;

	float x = (pTemp.x * cosf(theta)) - (pTemp.y * sinf(theta));
	float y = (pTemp.x * sinf(theta)) + (pTemp.y * cosf(theta));

	Vector2 vectorRotated(x, y);
	vectorRotated += anchor;

	return vectorRotated;
}

bool operator==(const Vector2& v1, const Vector2& v2)
{
	return v1.x == v2.x && v1.y == v2.y;
}

Vector2 operator+(const Vector2& v, const float& f)
{
	Vector2 vR = v;

	vR.AddNumber(f);

	return vR;
}

Vector2 operator+(const float& f, const Vector2& v)
{
	Vector2 vR = v;

	vR.AddNumber(f);

	return vR;
}

Vector2 operator-(const Vector2& v, const float& f)
{
	Vector2 vR = v;

	vR.AddNumber(-f);

	return vR;
}

Vector2 operator*(const Vector2& v, const float& f)
{
	Vector2 vR = v;

	vR.MultiplyNumber(f);

	return vR;
}

Vector2 operator*(const float& f, const Vector2& v)
{
	Vector2 vR = v;

	vR.MultiplyNumber(f);

	return vR;
}

Vector2 operator/(const Vector2& v, const float& f)
{
	Vector2 vR = v;

	vR.MultiplyNumber(1.f / f);

	return vR;
}

Vector2 operator+(const Vector2& v1, const Vector2& v2)
{
	Vector2 v;

	v = Vector2::Add(v1, v2);

	return v;
}

Vector2 operator-(const Vector2& v1, const Vector2& v2)
{
	Vector2 v;
	Vector2 v3 = v2;

	v3.Opposite();
	v = Vector2::Add(v1, v3);

	return v;
}

Vector2 operator*(const Vector2& v1, const Vector2& v2)
{
	Vector2 v;

	v = Vector2::Multiply(v1, v2);

	return v;
}

Vector2 operator/(const Vector2& v1, const Vector2& v2)
{
	Vector2 v;
	Vector2 v3 = v2;

	v3.Invert();
	v = Vector2::Multiply(v1, v3);

	return v;
}

Vector2 operator+=(Vector2& v, float& f)
{
	v.AddNumber(f);

	return v;
}

Vector2 operator-=(Vector2& v, float& f)
{
	v.AddNumber(-f);

	return v;
}

Vector2 operator*=(Vector2& v, float& f)
{
	v.MultiplyNumber(f);

	return v;
}

Vector2 operator/=(Vector2& v, float& f)
{
	v.MultiplyNumber(1.f / f);

	return v;
}

Vector2& operator+=(Vector2& v1, Vector2& v2)
{
	v1 = Vector2::Add(v1, v2);

	return v1;
}

Vector2& operator-=(Vector2& v1, Vector2& v2)
{
	v2.Opposite();

	v1 = Vector2::Add(v1, v2);

	return v1;
}

Vector2& operator*=(Vector2& v1, Vector2& v2)
{
	v1 = Vector2::Multiply(v1, v2);

	return v1;
}

Vector2& operator/=(Vector2& v1, Vector2& v2)
{
	v2.Invert();

	v1 = Vector2::Multiply(v1, v2);

	return v1;
}
