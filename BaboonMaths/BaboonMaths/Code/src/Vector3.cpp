#include "BaboonMaths.h"

Vector3::Vector3() : x(0.f), y(0.f), z(0.f) {}

Vector3::Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

Vector3::Vector3(float coords) : x(coords), y(coords), z(coords) {}

Vector3::Vector3(Vector4& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

void Vector3::Print()
{
	std::cout << "Vector3 : " << "x = " << x << ", y = " << y << ", z = " << z << std::endl;
}

void Vector3::BlankPrint()
{
	std::cout << x << "  " << y << "  " << z << std::endl;
}

void Vector3::Opposite()
{
	x *= -1.f;
	y *= -1.f;
	z *= -1.f;
}

void Vector3::Invert()
{
	x = 1 / x;
	y = 1 / y;
	z = 1 / z;
}

void Vector3::AddNumber(float number)
{
	x += number;
	y += number;
	z += number;
}

void Vector3::MultiplyNumber(float number)
{
	x *= number;
	y *= number;
	z *= number;
}

float Vector3::operator[](int index)
{
	if (index < 0 || index > 2)
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
}

Vector3 Vector3::Add(Vector3 v1, Vector3 v2)
{
	Vector3 v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;

	return v;
}

Vector3 Vector3::Multiply(Vector3 v1, Vector3 v2)
{
	Vector3 v;

	v.x = v1.x * v2.x;
	v.y = v1.y * v2.y;
	v.z = v1.z * v2.z;

	return v;
}

Vector3 Vector3::MidPoint(Vector3 v1, Vector3 v2)
{
	Vector3 v3;

	v3.x = (v1.x + v2.x) / 2;
	v3.y = (v1.y + v2.y) / 2;
	v3.z = (v1.z + v2.z) / 2;

	return v3;
}

float Vector3::Distance(Vector3 p1, Vector3 p2)
{
	float xSquared = powf(p1.x - p2.x, 2.f);
	float ySquared = powf(p1.y - p2.y, 2.f);
	float zSquared = powf(p1.z - p2.z, 2.f);
	float dist = sqrtf(xSquared + ySquared + zSquared);

	return dist;
}

float Vector3::SquaredNorm(Vector3 v)
{
	float xSquared = powf(v.x, 2.f);
	float ySquared = powf(v.y, 2.f);
	float zSquared = powf(v.z, 2.f);
	float squaredNorm = xSquared + ySquared + zSquared;

	return squaredNorm;
}

float Vector3::Norm(Vector3 v)
{
	float norm = sqrtf(Vector3::SquaredNorm(v));

	return norm;
}

Vector3 Vector3::Normalize(Vector3 v)
{
	float norm = Vector3::Norm(v);

	return { v.x / norm, v.y / norm, v.z / norm };
}

float Vector3::DotProduct(Vector3 v1, Vector3 v2)
{
	float dotProduct = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);

	return dotProduct;
}

Vector3 Vector3::CrossProduct(Vector3 v1, Vector3 v2)
{
	Vector3 v3;

	v3.x = (v1.y * v2.z) - (v1.z * v2.y);
	v3.y = (v1.z * v2.x) - (v1.x * v2.z);
	v3.z = (v1.x * v2.y) - (v1.y * v2.x);

	return v3;
}

float Vector3::GetAngle(Vector3 v1, Vector3 v2)
{
	float dotProduct = Vector3::DotProduct(v1, v2);
	float v1Norm = Vector3::Norm(v1);
	float v2Norm = Vector3::Norm(v2);

	if ((v1Norm * v2Norm) <= 0.0f)
		return 0.0f;

	float angle = acosf(dotProduct / (v1Norm * v2Norm));

	return angle;
}

Vector3 Vector3::Rotate(Vector3 p, float thetaX, float thetaY, float thetaZ)
{
	Matrix3x3 rotate = Matrix3x3::Rotation(thetaX, thetaY, thetaZ);

	Vector3 v = rotate * p;

	return v;
}

void Vector3::operator=(const Vector4& v2)
{
	x = v2.x;
	y = v2.y;
	z = v2.z;
}

bool operator==(const Vector3& v1, const Vector3& v2)
{
	return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

Vector3 operator+(const Vector3& v, const float& f)
{
	Vector3 vR = v;

	vR.AddNumber(f);

	return vR;
}

Vector3 operator+(const float& f, const Vector3& v)
{
	Vector3 vR = v;

	vR.AddNumber(f);

	return vR;
}

Vector3 operator-(const Vector3& v, const float& f)
{
	Vector3 vR = v;

	vR.AddNumber(-f);

	return vR;
}

Vector3 operator*(const Vector3& v, const float& f)
{
	Vector3 vR = v;

	vR.MultiplyNumber(f);

	return vR;
}

Vector3 operator*(const float& f, const Vector3& v)
{
	Vector3 vR = v;

	vR.MultiplyNumber(f);

	return vR;
}

Vector3 operator/(const Vector3& v, const float& f)
{
	Vector3 vR = v;

	vR.MultiplyNumber(1.f / f);

	return vR;
}

Vector3 operator+(const Vector3& v1, const Vector3& v2)
{
	Vector3 v;

	v = Vector3::Add(v1, v2);

	return v;
}

Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
	Vector3 v;
	Vector3 v3 = v2;

	v3.Opposite();
	v = Vector3::Add(v1, v3);

	return v;
}

Vector3 operator*(const Vector3& v1, const Vector3& v2)
{
	Vector3 v;

	v = Vector3::Multiply(v1, v2);

	return v;
}

Vector3 operator/(const Vector3& v1, const Vector3& v2)
{
	Vector3 v;
	Vector3 v3 = v2;

	v3.Invert();
	v = Vector3::Multiply(v1, v3);

	return v;
}

Vector3 operator+=(Vector3& v, float& f)
{
	v.AddNumber(f);
	return v;
}

Vector3 operator-=(Vector3& v, float& f)
{
	v.AddNumber(-f);
	return v;
}

Vector3 operator*=(Vector3& v, float& f)
{
	v.MultiplyNumber(f);
	return v;
}

Vector3 operator/=(Vector3& v, float& f)
{
	v.MultiplyNumber(1.f / f);
	return v;
}

Vector3& operator+=(Vector3& v1, Vector3& v2)
{
	v1 = Vector3::Add(v1, v2);

	return v1;
}

Vector3& operator-=(Vector3& v1, Vector3& v2)
{
	v2.Opposite();

	v1 = Vector3::Add(v1, v2);

	return v1;
}

Vector3& operator*=(Vector3& v1, Vector3& v2)
{
	v1 = Vector3::Multiply(v1, v2);

	return v1;
}

Vector3& operator/=(Vector3& v1, Vector3& v2)
{
	v2.Invert();

	v1 = Vector3::Multiply(v1, v2);

	return v1;
}