#include "BaboonMaths.h"

namespace Baboon
{
	Matrix2x2::Matrix2x2(bool identity)
	{
		switch (identity)
		{
		case false:
			elements = {
				0.f, 0.f ,
				0.f, 0.f
			};
			break;

		case true:
			elements = {
				1.f, 0.f ,
				0.f, 1.f
			};
			break;
		}
	}

	Matrix2x2::Matrix2x2(std::array<float, 4> _elements)
	{
		if (_elements.size() > 4)
			abort();

		elements = _elements;
	}

	void Matrix2x2::Print()
	{
		std::vector<Vector2> lines;
		lines.push_back({ elements[0], elements[1] });
		lines.push_back({ elements[2], elements[3] });
		std::cout << "Matrix 2x2 : " << std::endl;

		for (int i = 0; i < lines.size(); i++)
		{
			lines[i].BlankPrint();
		}

		std::cout << std::endl;
		lines.clear();
	}

	Vector2 Matrix2x2::Diagonal()
	{
		return Vector2(elements[0], elements[3]);
	}

	float Matrix2x2::Trace()
	{
		Vector2 diagonal = Diagonal();
		return diagonal.x + diagonal.y;
	}

	float Matrix2x2::operator[](int index)
	{
		if (index < 0 || index > 3)
		{
			std::cout << "Error : overflow" << std::endl;
			return NULL;
		}

		return elements[index];
	}

	void Matrix2x2::Opposite()
	{
		for (int i = 0; i < elements.size(); i++)
		{
			elements[i] *= -1;
		}
	}

	void Matrix2x2::Inverse()
	{
		float det = Determinant();
		if (det == 0) {
			return;
		}

		float invDet = 1.f / det;
		elements[0] = elements[3] * invDet;
		elements[1] = -elements[1] * invDet;
		elements[2] = -elements[2] * invDet;
		elements[3] = elements[0] * invDet;
	}

	void Matrix2x2::Transpose()
	{
		float temp;
		for (int i = 0; i < 2; ++i) {
			for (int j = i + 1; j < 2; ++j) {
				temp = elements[i * 2 + j];
				elements[i * 2 + j] = elements[j * 2 + i];
				elements[j * 2 + i] = temp;
			}
		}
	}

	void Matrix2x2::GaussJordan()
	{
		std::array<float, 4> newElements = elements;

		int lead = 0;
		for (int r = 0; r < 2; ++r) {
			if (3 <= lead)
				break;

			int i = r;
			while (newElements[i * 2 + lead] == 0) {
				++i;
				if (2 == i) {
					i = r;
					++lead;
					if (2 == lead)
						return;
				}
			}

			for (int j = 0; j < 2; ++j)
				std::swap(newElements[r * 2 + j], newElements[i * 2 + j]);

			float val = newElements[r * 2 + lead];
			for (int j = 0; j < 2; ++j)
				newElements[r * 2 + j] /= val;

			for (int i = 0; i < 2; ++i) {
				if (i != r) {
					float val = newElements[i * 2 + lead];
					for (int j = 0; j < 2; ++j)
						newElements[i * 2 + j] -= val * newElements[r * 2 + j];
				}
			}

			++lead;
		}
		elements = newElements;
	}

	float Matrix2x2::Determinant()
	{
		return (elements[0] * elements[3]) - (elements[1] * elements[2]);
	}

	Matrix2x2 Matrix2x2::Add(Matrix2x2 mat1, Matrix2x2 mat2)
	{
		Matrix2x2 m;
		for (int i = 0; i < 4; i++)
		{
			m.elements[i] = mat1[i] + mat2[i];
		}
		return m;
	}

	Matrix2x2 Matrix2x2::MultiplyNumber(Matrix2x2 mat, float number)
	{
		Matrix2x2 m;
		for (int i = 0; i < 4; i++)
		{
			m.elements[i] = mat[i] * number;
		}
		return m;
	}

	Matrix2x2 Matrix2x2::Multiply(Matrix2x2 mat1, Matrix2x2 mat2)
	{
		std::array<float, 4> result;

		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 2; ++j) {
				float sum = 0;
				for (int k = 0; k < 2; ++k) {
					sum += mat1.elements[i * 2 + k] * mat2.elements[k * 2 + j];
				}
				result[i * 2 + j] = sum;
			}
		}

		Matrix2x2 m(result);
		return m;
	}


	Matrix2x2 Matrix2x2::Rotation(float theta)
	{
		return Matrix2x2({
			cosf(theta), -sinf(theta),
			sinf(theta), cosf(theta)
			});
	}

	Matrix2x2 operator+(const Matrix2x2& mat1, const Matrix2x2& mat2)
	{
		Matrix2x2 m;
		m = Matrix2x2::Add(mat1, mat2);
		return m;
	}

	Matrix2x2 operator-(const Matrix2x2& mat1, const Matrix2x2& mat2)
	{
		Matrix2x2 m = mat2;
		m.Opposite();
		m = mat1 + m;
		return m;
	}

	Matrix2x2 operator*(const Matrix2x2& mat1, const Matrix2x2& mat2)
	{
		Matrix2x2 m;
		m = Matrix2x2::Multiply(mat1, mat2);
		return m;
	}

	Matrix2x2 operator*(const Matrix2x2& m, const float& f)
	{
		Matrix2x2 mat = Matrix2x2::MultiplyNumber(m, f);
		return mat;
	}

	Matrix2x2 operator*(const float& f, const Matrix2x2& m)
	{
		Matrix2x2 mat = Matrix2x2::MultiplyNumber(m, f);
		return mat;
	}

	Vector2 operator*(const Matrix2x2& m, const Vector2& v)
	{
		Vector2 vR;

		vR.x = (m.elements[0] * v.x) * (m.elements[1] * v.y);
		vR.x = (m.elements[2] * v.x) * (m.elements[3] * v.y);

		return vR;
	}

	Matrix2x2 operator+=(Matrix2x2& mat1, Matrix2x2& mat2)
	{
		mat1 = mat1 + mat2;
		return mat1;
	}

	Matrix2x2 operator-=(Matrix2x2& mat1, Matrix2x2& mat2)
	{
		mat1 = mat1 - mat2;
		return mat1;
	}

	Matrix2x2 operator*=(Matrix2x2& mat1, Matrix2x2& mat2)
	{
		mat1 = mat1 * mat2;
		return mat1;
	}

	Matrix2x2 operator*=(Matrix2x2& m, float& f)
	{
		m = m * f;
		return m;
	}
}
