#include "BaboonMaths.h"

namespace Baboon
{
	Matrix4x4::Matrix4x4(bool identity)
	{
		switch (identity)
		{
		case false:
			elements = {
				0.f, 0.f, 0.f, 0.f,
				0.f, 0.f, 0.f, 0.f,
				0.f, 0.f, 0.f, 0.f,
				0.f, 0.f, 0.f, 0.f
			};
			break;

		case true:
			elements = {
				1.f, 0.f, 0.f, 0.f,
				0.f, 1.f, 0.f, 0.f,
				0.f, 0.f, 1.f, 0.f,
				0.f, 0.f, 0.f, 1.f
			};
			break;
		}
	}

	Matrix4x4::Matrix4x4(std::array<float, 16> _elements)
	{
		if (_elements.size() > 16)
			abort();

		elements = _elements;
	}

	void Matrix4x4::Print()
	{
		std::vector<Vector4> lines;
		lines.push_back({ elements[0], elements[1], elements[2], elements[3] });
		lines.push_back({ elements[4], elements[5], elements[6], elements[7] });
		lines.push_back({ elements[8], elements[9], elements[10], elements[11] });
		lines.push_back({ elements[12], elements[13], elements[14], elements[15] });
		std::cout << "Matrix 4x4 : " << std::endl;

		for (int i = 0; i < lines.size(); i++)
		{
			lines[i].BlankPrint();
		}

		std::cout << std::endl;
		lines.clear();
	}

	Vector4 Matrix4x4::Diagonal()
	{
		return Vector4(elements[0], elements[5], elements[10], elements[15]);
	}

	float Matrix4x4::Trace()
	{
		Vector4 diagonal = Diagonal();
		return diagonal.x + diagonal.y + diagonal.z + diagonal.w;
	}

	float Matrix4x4::operator[](int index)
	{
		if (index < 0 || index > 15)
		{
			std::cout << "Error : overflow" << std::endl;
			return NULL;
		}

		return elements[index];
	}

	void Matrix4x4::Opposite()
	{
		for (int i = 0; i < elements.size(); i++)
		{
			elements[i] *= -1;
		}
	}

	void Matrix4x4::Inverse()
	{
		float det = Determinant();
		if (det == 0) {
			std::cout << "Cannot invert 4x4 matrix" << std::endl;
			exit(1);
		}

		Matrix4x4 cofactorMatrix = Comatrix();
		cofactorMatrix.Transpose();

		float invDet = 1.f / det;
		elements = Matrix4x4::MultiplyNumber(cofactorMatrix, invDet).elements;
	}

	void Matrix4x4::Transpose()
	{
		float temp;
		for (int i = 0; i < 4; ++i) {
			for (int j = i + 1; j < 4; ++j) {
				temp = elements[i * 4 + j];
				elements[i * 4 + j] = elements[j * 4 + i];
				elements[j * 4 + i] = temp;
			}
		}
	}

	void Matrix4x4::GaussJordan()
	{
		std::array<float, 16> newElements = elements;

		int lead = 0;
		for (int r = 0; r < 4; ++r) {
			if (4 <= lead)
				break;

			int i = r;
			while (newElements[i * 4 + lead] == 0) {
				++i;
				if (4 == i) {
					i = r;
					++lead;
					if (4 == lead)
						return;
				}
			}

			for (int j = 0; j < 4; ++j)
				std::swap(newElements[r * 4 + j], newElements[i * 4 + j]);

			float val = newElements[r * 4 + lead];
			for (int j = 0; j < 4; ++j)
				newElements[r * 4 + j] /= val;

			for (int i = 0; i < 4; ++i) {
				if (i != r) {
					float val = newElements[i * 4 + lead];
					for (int j = 0; j < 4; ++j)
						newElements[i * 4 + j] -= val * newElements[r * 4 + j];
				}
			}

			++lead;
		}

		elements = newElements;
	}

	float Matrix4x4::Determinant()
	{
		float det = 0;
		Matrix3x3 mat1({
			elements[5], elements[6], elements[7],
			elements[9], elements[10], elements[11],
			elements[13], elements[14], elements[15]
			});
		Matrix3x3 mat2({
			elements[4], elements[6], elements[7],
			elements[8], elements[10], elements[11],
			elements[12], elements[14], elements[15]
			});
		Matrix3x3 mat3({
			elements[4], elements[5], elements[7],
			elements[8], elements[9], elements[11],
			elements[12], elements[13], elements[15]
			});
		Matrix3x3 mat4({
			elements[4], elements[5], elements[6],
			elements[8], elements[9], elements[10],
			elements[12], elements[13], elements[14]
			});
		det += elements[0] * mat1.Determinant();
		det -= elements[1] * mat2.Determinant();
		det += elements[2] * mat3.Determinant();
		det -= elements[3] * mat4.Determinant();
		return det;
	}

	Matrix4x4 Matrix4x4::Comatrix() const
	{
		Matrix4x4 solution;

		for (size_t i = 0; i < 4; ++i) {
			for (size_t j = 0; j < 4; ++j) {
				Matrix3x3 subMatrix;
				int p = 0, q = 0;
				for (size_t x = 0; x < 4; ++x) {
					if (x == i) continue;
					q = 0;
					for (size_t y = 0; y < 4; ++y) {
						if (y == j) continue;
						subMatrix.elements[p * 3 + q] = elements[x * 4 + y];
						++q;
					}
					++p;
				}
				float cofactorSign = ((i + j) % 2 == 0) ? 1.f : -1.f;
				solution.elements[i * 4 + j] = cofactorSign * subMatrix.Determinant();
			}
		}

		return solution;
	}

	Matrix4x4 Matrix4x4::Homogeneous(Matrix3x3 m)
	{
		return Matrix4x4({
			m.elements[0], m.elements[1], m.elements[2], 0.f,
			m.elements[3], m.elements[4], m.elements[5], 0.f,
			m.elements[6], m.elements[7], m.elements[8], 0.f,
			0.f, 0.f, 0.f, 1.f
			});
	}

	Matrix4x4 Matrix4x4::Add(Matrix4x4 mat1, Matrix4x4 mat2)
	{
		Matrix4x4 m;
		for (int i = 0; i < 16; i++)
		{
			m.elements[i] = mat1[i] + mat2[i];
		}
		return m;
	}

	Matrix4x4 Matrix4x4::MultiplyNumber(Matrix4x4 mat, float number)
	{
		Matrix4x4 m;
		for (int i = 0; i < 16; i++)
		{
			m.elements[i] = mat[i] * number;
		}
		return m;
	}

	Matrix4x4 Matrix4x4::Multiply(Matrix4x4 mat1, Matrix4x4 mat2)
	{
		std::array<float, 16> result;

		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				float sum = 0;
				for (int k = 0; k < 4; ++k) {
					sum += mat1.elements[i * 4 + k] * mat2.elements[k * 4 + j];
				}
				result[i * 4 + j] = sum;
			}
		}
		Matrix4x4 m(result);
		return m;
	}

	Matrix4x4 Matrix4x4::TRS(Vector3 translation, Vector3 rotation, Vector3 scaling)
	{
		Matrix4x4 translate({
			1.f, 0.f, 0.f, translation.x,
			0.f, 1.f, 0.f, translation.y,
			0.f, 0.f, 1.f, translation.z,
			0.f, 0.f, 0.f, 1.f
			});

		Matrix4x4 rotate = Matrix4x4::Homogeneous(Matrix3x3::Rotation(rotation.x, rotation.y, rotation.z));

		Matrix4x4 scale({
			scaling.x, 0.f, 0.f, 0.f,
			0.f, scaling.y, 0.f, 0.f,
			0.f, 0.f, scaling.z, 0.f,
			0.f, 0.f, 0.f, 1.f
			});

		Matrix4x4 TRS = translate * (rotate * scale);

		return TRS;
	}

	Matrix4x4 Matrix4x4::View(Vector3 up, Vector3 center, Vector3 eye)
	{
		Vector3 f = Vector3::Normalize(center - eye);
		Vector3 r = Vector3::Normalize(Vector3::CrossProduct(f, up));
		Vector3 u = Vector3::CrossProduct(r, f);

		Matrix4x4 view({
			r.x, r.y, r.z, -1.f * Vector3::DotProduct(r, eye),
			u.x, u.y, u.z, -1.f * Vector3::DotProduct(u, eye),
			-f.x, -f.y, -f.z, Vector3::DotProduct(f, eye),
			0.f, 0.f, 0.f, 1.f
			});

		return view;
	}

	Matrix4x4 Matrix4x4::Perspective(float fovY, float aspect, float near, float far)
	{
		return Matrix4x4({
			1.f / (aspect * tanf(fovY / 2.f)), 0.f, 0.f, 0.f,
			0.f, 1.f / (tanf(fovY / 2.f)), 0.f, 0.f,
			0.f, 0.f, -1.f * (far + near) / (far - near), -1.f * (2.f * far * near) / (far - near),
			0.f, 0.f, -1.f, 0.f
			});
	}

	Matrix4x4 Matrix4x4::Orthographic(float top, float bottom, float right, float left, float far, float near)
	{
		return Matrix4x4({
			2.f / (right - left), 0.f, 0.f, -1.f * ((right + left) / (right - left)),
			0.f, 2.f / (top - bottom), 0.f, -1.f * ((top + bottom) / (top - bottom)),
			0.f, 0.f, -2.f / (far - near), -1.f * ((far + near) / (far - near)),
			0.f, 0.f, 0.f, 1.f
			});
	}

	Matrix4x4 operator+(const Matrix4x4& mat1, const Matrix4x4& mat2)
	{
		Matrix4x4 m;
		m = Matrix4x4::Add(mat1, mat2);
		return m;
	}

	Matrix4x4 operator-(const Matrix4x4& mat1, const Matrix4x4& mat2)
	{
		Matrix4x4 m = mat2;
		m.Opposite();
		m = Matrix4x4::Add(mat1, mat2);
		return m;
	}

	Matrix4x4 operator*(const Matrix4x4& mat1, const Matrix4x4& mat2)
	{
		Matrix4x4 m;
		m = Matrix4x4::Multiply(mat1, mat2);
		return m;
	}

	Matrix4x4 operator*(const Matrix4x4& m, const float& f)
	{
		Matrix4x4 mat = Matrix4x4::MultiplyNumber(m, f);
		return mat;
	}

	Matrix4x4 operator*(const float& f, const Matrix4x4& m)
	{
		Matrix4x4 mat = Matrix4x4::MultiplyNumber(m, f);
		return mat;
	}

	Vector4 operator*(const Matrix4x4& m, const Vector4& v)
	{
		Vector4 vR;
		vR.x = (m.elements[0] * v.x) + (m.elements[1] * v.y) + (m.elements[2] * v.z) + (m.elements[3] * v.w);
		vR.y = (m.elements[4] * v.x) + (m.elements[5] * v.y) + (m.elements[6] * v.z) + (m.elements[7] * v.w);
		vR.z = (m.elements[8] * v.x) + (m.elements[9] * v.y) + (m.elements[10] * v.z) + (m.elements[11] * v.w);
		vR.w = (m.elements[12] * v.x) + (m.elements[13] * v.y) + (m.elements[14] * v.z) + (m.elements[15] * v.w);
		return vR;
	}

	Matrix4x4 operator+=(Matrix4x4& mat1, Matrix4x4& mat2)
	{
		mat1 = mat1 + mat2;
		return mat1;
	}

	Matrix4x4 operator-=(Matrix4x4& mat1, Matrix4x4& mat2)
	{
		mat1 = mat1 - mat2;
		return mat1;
	}

	Matrix4x4 operator*=(Matrix4x4& mat1, Matrix4x4& mat2)
	{
		mat1 = mat1 * mat2;
		return mat1;
	}

	Matrix4x4 operator*=(Matrix4x4& m, float& f)
	{
		m = m * f;
		return m;
	}
}
