#include "BaboonMaths.h"

Matrix3x3::Matrix3x3(bool identity)
{
	switch (identity)
	{
	case false:
		elements = {
			0.f, 0.f, 0.f,
			0.f, 0.f, 0.f,
			0.f, 0.f, 0.f
		};
		break;

	case true:
		elements = {
			1.f, 0.f, 0.f,
			0.f, 1.f, 0.f,
			0.f, 0.f, 1.f
		};
		break;
	}
}

Matrix3x3::Matrix3x3(std::array<float, 9> _elements)
{
	if (_elements.size() > 9)
		abort();

	elements = _elements;
}

void Matrix3x3::Print()
{
	std::vector<Vector3> lines;
	lines.push_back({ elements[0], elements[1], elements[2] });
	lines.push_back({ elements[3], elements[4], elements[5] });
	lines.push_back({ elements[6], elements[7], elements[8] });
	std::cout << "Matrix 3x3 : " << std::endl;

	for (int i = 0; i < lines.size(); i++)
	{
		lines[i].BlankPrint();
	}

	std::cout << std::endl;
}

Vector3 Matrix3x3::Diagonal()
{
	return Vector3(elements[0], elements[4], elements[8]);
}

float Matrix3x3::Trace()
{
	Vector3 diagonal = Diagonal();
	return diagonal.x + diagonal.y + diagonal.z;
}

float Matrix3x3::operator[](int index)
{
	if (index < 0 || index > 8)
	{
		std::cout << "Error : overflow" << std::endl;
		return NULL;
	}

	return elements[index];
}

void Matrix3x3::Opposite()
{
	for (int i = 0; i < elements.size(); i++)
	{
		elements[i] *= -1;
	}
}

void Matrix3x3::Inverse()
{
	float det = Determinant();
	if (det == 0) {
		return;
	}

	float invDet = 1.0 / det;
	elements[0] = (elements[4] * elements[8] - elements[5] * elements[7]) * invDet;
	elements[1] = (elements[2] * elements[7] - elements[1] * elements[8]) * invDet;
	elements[2] = (elements[1] * elements[5] - elements[2] * elements[4]) * invDet;
	elements[3] = (elements[5] * elements[6] - elements[3] * elements[8]) * invDet;
	elements[4] = (elements[0] * elements[8] - elements[2] * elements[6]) * invDet;
	elements[5] = (elements[2] * elements[3] - elements[0] * elements[5]) * invDet;
	elements[6] = (elements[3] * elements[7] - elements[4] * elements[6]) * invDet;
	elements[7] = (elements[1] * elements[6] - elements[0] * elements[7]) * invDet;
	elements[8] = (elements[0] * elements[4] - elements[1] * elements[3]) * invDet;
}

void Matrix3x3::Transpose()
{
	float temp;
	for (int i = 0; i < 3; ++i) {
		for (int j = i + 1; j < 3; ++j) {
			temp = elements[i * 3 + j];
			elements[i * 3 + j] = elements[j * 3 + i];
			elements[j * 3 + i] = temp;
		}
	}
}

void Matrix3x3::GaussJordan()
{
	std::array<float, 9> newElements = elements;

	int lead = 0;
	for (int r = 0; r < 3; ++r) {
		if (3 <= lead)
			break;

		int i = r;
		while (newElements[i * 3 + lead] == 0) {
			++i;
			if (3 == i) {
				i = r;
				++lead;
				if (3 == lead)
					return;
			}
		}

		for (int j = 0; j < 3; ++j)
			std::swap(newElements[r * 3 + j], newElements[i * 3 + j]);

		float val = newElements[r * 3 + lead];
		for (int j = 0; j < 3; ++j)
			newElements[r * 3 + j] /= val;

		for (int i = 0; i < 3; ++i) {
			if (i != r) {
				float val = newElements[i * 3 + lead];
				for (int j = 0; j < 3; ++j)
					newElements[i * 3 + j] -= val * newElements[r * 3 + j];
			}
		}

		++lead;
	}
	elements = newElements;
}

float Matrix3x3::Determinant()
{
	float det = elements[0] * (elements[4] * elements[8] - elements[5] * elements[7])
		- elements[1] * (elements[3] * elements[8] - elements[5] * elements[6])
		+ elements[2] * (elements[3] * elements[7] - elements[4] * elements[6]);
	return det;
}

Matrix3x3 Matrix3x3::Add(Matrix3x3 mat1, Matrix3x3 mat2)
{
	Matrix3x3 m;
	for (int i = 0; i < 9; i++)
	{
		m.elements[i] = mat1[i] + mat2[i];
	}
	return m;
}

Matrix3x3 Matrix3x3::MultiplyNumber(Matrix3x3 mat, float number)
{
	Matrix3x3 m;
	for (int i = 0; i < 9; i++)
	{
		m.elements[i] = mat[i] * number;
	}
	return m;
}

Matrix3x3 Matrix3x3::Multiply(Matrix3x3 mat1, Matrix3x3 mat2)
{
	std::array<float, 9> result;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			float sum = 0;
			for (int k = 0; k < 3; ++k) {
				sum += mat1.elements[i * 3 + k] * mat2.elements[k * 3 + j];
			}
			result[i * 3 + j] = sum;
		}
	}
	Matrix3x3 m(result);
	return m;
}

Matrix3x3 Matrix3x3::Rotation(float thetaX, float thetaY, float thetaZ)
{
	return RotationZ(thetaZ) * RotationY(thetaY) * RotationX(thetaX);
}

Matrix3x3 Matrix3x3::RotationX(float thetaX)
{
	return Matrix3x3({
		1.f, 0.f, 0.f,
		0.f, cosf(thetaX), -sinf(thetaX),
		0.f, sinf(thetaX), cosf(thetaX)
		});
}

Matrix3x3 Matrix3x3::RotationY(float thetaY)
{
	return Matrix3x3({
		cosf(thetaY), 0.f, sinf(thetaY),
		0.f, 1.f, 0.f,
		-sinf(thetaY), 0.f, cosf(thetaY)
		});
}

Matrix3x3 Matrix3x3::RotationZ(float thetaZ)
{
	return Matrix3x3({
		cosf(thetaZ), -sinf(thetaZ), 0.f,
		sinf(thetaZ), cosf(thetaZ), 0.f,
		0.f, 0.f, 1.f
		});
}

Matrix3x3 operator+(const Matrix3x3& mat1, const Matrix3x3& mat2)
{
	Matrix3x3 m;
	m = Matrix3x3::Add(mat1, mat2);
	return m;
}

Matrix3x3 operator-(const Matrix3x3& mat1, const Matrix3x3& mat2)
{
	Matrix3x3 m = mat2;
	m.Opposite();
	m = Matrix3x3::Add(mat1, m);
	return m;
}

Matrix3x3 operator*(const Matrix3x3& mat1, const Matrix3x3& mat2)
{
	Matrix3x3 m;
	m = Matrix3x3::Multiply(mat1, mat2);
	return m;
}

Matrix3x3 operator*(const Matrix3x3& m, const float& f)
{
	Matrix3x3 mat = Matrix3x3::MultiplyNumber(m, f);
	return mat;
}

Matrix3x3 operator*(const float& f, const Matrix3x3& m)
{
	Matrix3x3 mat = Matrix3x3::MultiplyNumber(m, f);
	return mat;
}

Vector3 operator*(const Matrix3x3& m, const Vector3& v)
{
	Vector3 vR;

	vR.x = (m.elements[0] * v.x) + (m.elements[1] * v.y) + (m.elements[2] * v.z);
	vR.y = (m.elements[3] * v.x) + (m.elements[4] * v.y) + (m.elements[5] * v.z);
	vR.z = (m.elements[6] * v.x) + (m.elements[7] * v.y) + (m.elements[8] * v.z);

	return vR;
}

Matrix3x3 operator+=(Matrix3x3& mat1, Matrix3x3& mat2)
{
	mat1 = mat1 + mat2;
	return mat1;
}

Matrix3x3 operator-=(Matrix3x3& mat1, Matrix3x3& mat2)
{
	mat1 = mat1 - mat2;
	return mat1;
}

Matrix3x3 operator*=(Matrix3x3& mat1, Matrix3x3& mat2)
{
	mat1 = mat1 * mat2;
	return mat1;
}

Matrix3x3 operator*=(Matrix3x3& m, float& f)
{
	m = m * f;
	return m;
}
