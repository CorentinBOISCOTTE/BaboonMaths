#include "BaboonMaths.h"

Vector4::Vector4() : x(0.f), y(0.f), z(0.f), w(0.f) {}

Vector4::Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}

Vector4::Vector4(float coords) : x(coords), y(coords), z(coords), w(coords) {}

void Vector4::Print()
{
	std::cout << "Vector4 : " << "x = " << x << ", y = " << y << ", z = " << z << ", w = " << w << std::endl;
}

void Vector4::BlankPrint()
{
	std::cout << x << "  " << y << "  " << z << "  " << w << std::endl;
}

void Vector4::Opposite()
{
	x *= -1.f;
	y *= -1.f;
	z *= -1.f;
	w *= -1.f;
}

void Vector4::Invert()
{
	x = 1 / x;
	y = 1 / y;
	z = 1 / z;
	w = 1 / w;
}

void Vector4::AddNumber(float number)
{
	x += number;
	y += number;
	z += number;
	w += number;
}

void Vector4::MultiplyNumber(float number)
{
	x *= number;
	y *= number;
	z *= number;
	w *= number;
}

float Vector4::operator[](int index)
{
	if (index < 0 || index > 3)
	{
		std::cout << "Error : overflow" << std::endl;
		return NULL;
	}

	if (index == 0)
		return x;
	else if (index == 1)
		return y;
	else if (index == 2)
		return z;
	else if (index == 3)
		return w;
}

Vector4 Vector4::Vector3Homogeneous(Vector3 v, float w)
{
	return Vector4(v.x, v.y, v.z, w);
}

Vector4 Vector4::Add(Vector4 v1, Vector4 v2)
{
	Vector4 v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	v.w = v1.w + v2.w;

	return v;
}

Vector4 Vector4::Multiply(Vector4 v1, Vector4 v2)
{
	Vector4 v;

	v.x = v1.x * v2.x;
	v.y = v1.y * v2.y;
	v.z = v1.z * v2.z;
	v.w = v1.w * v2.w;

	return v;
}

Vector4 Vector4::MidPoint(Vector4 v1, Vector4 v2)
{
	Vector4 v3;

	v3.x = (v1.x + v2.x) / 2;
	v3.y = (v1.y + v2.y) / 2;
	v3.z = (v1.z + v2.z) / 2;
	v3.w = (v1.w + v2.w) / 2;

	return v3;
}

float Vector4::Distance(Vector4 p1, Vector4 p2)
{
	float xSquared = powf(p1.x - p2.x, 2.f);
	float ySquared = powf(p1.y - p2.y, 2.f);
	float zSquared = powf(p1.z - p2.z, 2.f);
	float wSquared = powf(p1.w - p2.w, 2.f);
	float dist = sqrtf(xSquared + ySquared + zSquared + wSquared);

	return dist;
}

float Vector4::SquaredNorm(Vector4 v)
{
	float xSquared = powf(v.x, 2.f);
	float ySquared = powf(v.y, 2.f);
	float zSquared = powf(v.z, 2.f);
	float wSquared = powf(v.w, 2.f);
	float squaredNorm = xSquared + ySquared + zSquared + wSquared;

	return squaredNorm;
}

float Vector4::Norm(Vector4 v)
{
	float norm = sqrtf(Vector4::SquaredNorm(v));

	return norm;
}

Vector4 Vector4::Normalize(Vector4 v)
{
	float norm = Vector4::Norm(v);

	return { v.x / norm, v.y / norm, v.z / norm, v.w / norm };
}

float Vector4::DotProduct(Vector4 v1, Vector4 v2)
{
	float dotProduct = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);

	return dotProduct;
}

bool operator==(const Vector4& v1, const Vector4& v2)
{
	return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
}

Vector4 operator+(const Vector4& v, const float& f)
{
	Vector4 vR = v;

	vR.AddNumber(f);

	return vR;
}

Vector4 operator+(const float& f, const Vector4& v)
{
	Vector4 vR = v;

	vR.AddNumber(f);

	return vR;
}

Vector4 operator-(const Vector4& v, const float& f)
{
	Vector4 vR = v;

	vR.AddNumber(-f);

	return vR;
}

Vector4 operator*(const Vector4& v, const float& f)
{
	Vector4 vR = v;

	vR.MultiplyNumber(f);

	return vR;
}

Vector4 operator*(const float& f, const Vector4& v)
{
	Vector4 vR = v;

	vR.MultiplyNumber(f);

	return vR;
}

Vector4 operator/(const Vector4& v, const float& f)
{
	Vector4 vR = v;

	vR.MultiplyNumber(1.f / f);

	return vR;
}

Vector4 operator+(const Vector4& v1, const Vector4& v2)
{
	Vector4 v;

	v = Vector4::Add(v1, v2);

	return v;
}

Vector4 operator-(const Vector4& v1, const Vector4& v2)
{
	Vector4 v;
	Vector4 v3 = v2;

	v3.Opposite();
	v = Vector4::Add(v1, v3);

	return v;
}

Vector4 operator*(const Vector4& v1, const Vector4& v2)
{
	Vector4 v;

	v = Vector4::Multiply(v1, v2);

	return v;
}

Vector4 operator/(const Vector4& v1, const Vector4& v2)
{
	Vector4 v;
	Vector4 v3 = v2;

	v3.Invert();
	v = Vector4::Multiply(v1, v3);

	return v;
}

Vector4 operator+=(Vector4& v, float& f)
{
	v.AddNumber(f);

	return v;
}

Vector4 operator-=(Vector4& v, float& f)
{
	v.AddNumber(-f);
	
	return v;
}

Vector4 operator*=(Vector4& v, float& f)
{
	v.MultiplyNumber(f);

	return v;
}

Vector4 operator/=(Vector4& v, float& f)
{
	v.MultiplyNumber(1.f / f);

	return v;
}

Vector4& operator+=(Vector4& v1, Vector4& v2)
{
	v1 = Vector4::Add(v1, v2);

	return v1;
}

Vector4& operator-=(Vector4& v1, Vector4& v2)
{
	v2.Opposite();

	v1 = Vector4::Add(v1, v2);

	return v1;
}

Vector4& operator*=(Vector4& v1, Vector4& v2)
{
	v1 = Vector4::Multiply(v1, v2);

	return v1;
}

Vector4& operator/=(Vector4& v1, Vector4& v2)
{
	v2.Invert();

	v1 = Vector4::Multiply(v1, v2);

	return v1;
}