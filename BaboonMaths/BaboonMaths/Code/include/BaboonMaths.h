#pragma once
#include <iostream>
#include <stdio.h>
#include <stdarg.h>
#include <vector>
#include <array>

namespace Baboon
{
	constexpr auto PI = 3.14159265358979323846f;

	class Vector2;
	class Vector3;
	class Vector4;
	class Matrix2x2;
	class Matrix3x3;
	class Matrix4x4;

	float ToRadians(float deg);
	float ToDegrees(float rad);

	//Class for Vector2
	class Vector2
	{
	public:
		// vector components
		float x;
		float y;

		// different ways of initializing a vector
		Vector2();
		Vector2(float _x, float _y);
		Vector2(float coords);
		~Vector2() = default;

		// different print methods
		void Print();
		void BlankPrint();

		void Opposite(); // returns the vector's opposite
		void Invert(); // returns the vector's invert
		void AddNumber(float number); // adds a number to the vector
		void MultiplyNumber(float number); // multiplies the vector by a number

		float operator[](int index); // get a component with an index

		static Vector2 Add(Vector2 v1, Vector2 v2); // adds two vectors
		static Vector2 Multiply(Vector2 v1, Vector2 v2); // multiplies two vectors
		static Vector2 MidPoint(Vector2 v1, Vector2 v2); // get the mid point of two points
		static float Distance(Vector2 p1, Vector2 p2); // get the distance between two points
		static float SquaredNorm(Vector2 v); // returns the squared norm of a vector
		static float Norm(Vector2 v); // returns the norm of a vector
		static Vector2 Normalize(Vector2 v); //returns normalized vector
		static float DotProduct(Vector2 v1, Vector2 v2); // returns the dot product of two vectors
		static float CrossProduct(Vector2 v1, Vector2 v2); // returns the cross product of two vectors
		static float GetAngle(Vector2 v1, Vector2 v2); // returns the angle between two vectors
		static Vector2 Rotate(Vector2 p, float theta, Vector2 anchor = Vector2()); // rotates a point around another point
	};

	bool operator==(const Vector2& v1, const Vector2& v2);
	Vector2 operator+(const Vector2& v, const float& f);
	Vector2 operator+(const float& f, const Vector2& v);
	Vector2 operator-(const Vector2& v, const float& f);
	Vector2 operator*(const Vector2& v, const float& f);
	Vector2 operator*(const float& f, const Vector2& v);
	Vector2 operator/(const Vector2& v, const float& f);
	Vector2 operator+(const Vector2& v1, const Vector2& v2);
	Vector2 operator-(const Vector2& v1, const Vector2& v2);
	Vector2 operator*(const Vector2& v1, const Vector2& v2);
	Vector2 operator/(const Vector2& v1, const Vector2& v2);
	Vector2 operator+=(Vector2& v, float& f);
	Vector2 operator-=(Vector2& v, float& f);
	Vector2 operator*=(Vector2& v, float& f);
	Vector2 operator/=(Vector2& v, float& f);
	Vector2& operator+=(Vector2& v1, Vector2& v2);
	Vector2& operator-=(Vector2& v1, Vector2& v2);
	Vector2& operator*=(Vector2& v1, Vector2& v2);
	Vector2& operator/=(Vector2& v1, Vector2& v2);

	//Class for Vector3
	class Vector3
	{
	public:
		// vector components
		float x;
		float y;
		float z;

		// different ways of initializing a vector
		Vector3();
		Vector3(float _x, float _y, float _z);
		Vector3(float coords);
		Vector3(Vector4& v);
		~Vector3() = default;

		// different print methods
		void Print();
		void BlankPrint();

		void Opposite(); // returns the vector's opposite
		void Invert(); // returns the vector's invert
		void AddNumber(float number); // adds a number to the vector
		void MultiplyNumber(float number); // multiplies the vector by a number

		float operator[](int index); // get a component with an index
		void operator=(const Vector4& v2);

		static Vector3 Add(Vector3 v1, Vector3 v2);  // adds two vectors
		static Vector3 Multiply(Vector3 v1, Vector3 v2); // multiplies two vectors
		static Vector3 MidPoint(Vector3 v1, Vector3 v2); // get the mid point of two points
		static float Distance(Vector3 p1, Vector3 p2); // get the distance between two points
		static float SquaredNorm(Vector3 v); // returns the squared norm of a vector
		static float Norm(Vector3 v); // returns the norm of a vector
		static Vector3 Normalize(Vector3 v); //returns normalized vector
		static float DotProduct(Vector3 v1, Vector3 v2); // returns the dot product of two vectors
		static Vector3 CrossProduct(Vector3 v1, Vector3 v2); // returns the cross product of two vectors
		static float GetAngle(Vector3 v1, Vector3 v2); // returns the angle between two vectors
		static Vector3 Rotate(Vector3 p, float thetaX, float thetaY, float thetaZ); // rotates a point with the 3D rotation matrix
	};

	bool operator==(const Vector3& v1, const Vector3& v2);
	Vector3 operator+(const Vector3& v, const float& f);
	Vector3 operator+(const float& f, const Vector3& v);
	Vector3 operator-(const Vector3& v, const float& f);
	Vector3 operator*(const Vector3& v, const float& f);
	Vector3 operator*(const float& f, const Vector3& v);
	Vector3 operator/(const Vector3& v, const float& f);
	Vector3 operator+(const Vector3& v1, const Vector3& v2);
	Vector3 operator-(const Vector3& v1, const Vector3& v2);
	Vector3 operator*(const Vector3& v1, const Vector3& v2);
	Vector3 operator/(const Vector3& v1, const Vector3& v2);
	Vector3 operator+=(Vector3& v, float& f);
	Vector3 operator-=(Vector3& v, float& f);
	Vector3 operator*=(Vector3& v, float& f);
	Vector3 operator/=(Vector3& v, float& f);
	Vector3& operator+=(Vector3& v1, Vector3& v2);
	Vector3& operator-=(Vector3& v1, Vector3& v2);
	Vector3& operator*=(Vector3& v1, Vector3& v2);
	Vector3& operator/=(Vector3& v1, Vector3& v2);

	//Class for Vector4
	class Vector4
	{
	public:
		// vector components
		float x;
		float y;
		float z;
		float w;

		// different ways of initializing a vector
		Vector4();
		Vector4(float _x, float _y, float _z, float _w);
		Vector4(float coords);
		~Vector4() = default;

		// different print methods
		void Print();
		void BlankPrint();

		void Opposite(); // returns the vector's opposite
		void Invert(); // returns the vector's invert
		void AddNumber(float number); // adds a number to the vector
		void MultiplyNumber(float number); // multiplies the vector by a number

		float operator[](int index); // get a component with an index

		static Vector4 Vector3Homogeneous(Vector3 v, float w); // vector3D -> Vector4
		static Vector4 Add(Vector4 v1, Vector4 v2);  // adds two vectors
		static Vector4 Multiply(Vector4 v1, Vector4 v2); // multiplies two vectors
		static Vector4 MidPoint(Vector4 v1, Vector4 v2); // get the mid point of two points
		static float Distance(Vector4 p1, Vector4 p2); // get the distance between two points
		static float SquaredNorm(Vector4 v); // returns the squared norm of a vector
		static float Norm(Vector4 v); // returns the norm of a vector
		static Vector4 Normalize(Vector4 v); //returns normalized vector
		static float DotProduct(Vector4 v1, Vector4 v2); // returns the dot product of two vectors
	};

	bool operator==(const Vector4& v1, const Vector4& v2);
	Vector4 operator+(const Vector4& v, const float& f);
	Vector4 operator+(const float& f, const Vector4& v);
	Vector4 operator-(const Vector4& v, const float& f);
	Vector4 operator*(const Vector4& v, const float& f);
	Vector4 operator*(const float& f, const Vector4& v);
	Vector4 operator/(const Vector4& v, const float& f);
	Vector4 operator+(const Vector4& v1, const Vector4& v2);
	Vector4 operator-(const Vector4& v1, const Vector4& v2);
	Vector4 operator*(const Vector4& v1, const Vector4& v2);
	Vector4 operator/(const Vector4& v1, const Vector4& v2);
	Vector4 operator+=(Vector4& v, float& f);
	Vector4 operator-=(Vector4& v, float& f);
	Vector4 operator*=(Vector4& v, float& f);
	Vector4 operator/=(Vector4& v, float& f);
	Vector4& operator+=(Vector4& v1, Vector4& v2);
	Vector4& operator-=(Vector4& v1, Vector4& v2);
	Vector4& operator*=(Vector4& v1, Vector4& v2);
	Vector4& operator/=(Vector4& v1, Vector4& v2);

	// Class for 2x2 Matrices
	class Matrix2x2
	{
	public:
		std::array<float, 4> elements;//vector to save the matrix's elements

		// Different ways of initializing a matrix
		Matrix2x2(bool identity = false);
		Matrix2x2(std::array<float, 4> _elements);
		~Matrix2x2() = default;

		void Print(); // Displays the matrix

		Vector2 Diagonal(); // method that returns the diagonal
		float Trace(); // method that returns the trace

		float operator[](int index); // operator to get any element of the matirx with the index

		void Opposite(); // returns the opposite of a matrix
		void Inverse();
		void Transpose(); // transposes a matrix and returns it
		void GaussJordan();
		float Determinant(); // returns the determinant of a matrix

		static Matrix2x2 Add(Matrix2x2 mat1, Matrix2x2 mat2); // adds two matrices
		static Matrix2x2 MultiplyNumber(Matrix2x2 mat, float number); // multiplies a matrix by a number
		static Matrix2x2 Multiply(Matrix2x2 mat1, Matrix2x2 mat2); // multiplies two matrices
		static Matrix2x2 Rotation(float theta); // returns a 2D rotation matrix
	};

	Matrix2x2 operator+(const Matrix2x2& mat1, const Matrix2x2& mat2); // overloads + operator to add matrices
	Matrix2x2 operator-(const Matrix2x2& mat1, const Matrix2x2& mat2);
	Matrix2x2 operator*(const Matrix2x2& mat1, const Matrix2x2& mat2); // overloads * operator to multiply matrices
	Matrix2x2 operator*(const Matrix2x2& m, const float& f);
	Matrix2x2 operator*(const float& f, const Matrix2x2& m);
	Vector2 operator*(const Matrix2x2& m, const Vector2& v); // overloads * operator to multiply a matrix by a 2D vector
	Matrix2x2 operator+=(Matrix2x2& mat1, Matrix2x2& mat2);
	Matrix2x2 operator-=(Matrix2x2& mat1, Matrix2x2& mat2);
	Matrix2x2 operator*=(Matrix2x2& mat1, Matrix2x2& mat2);
	Matrix2x2 operator*=(Matrix2x2& m, float& f);

	// Class for 3x3 Matrices
	class Matrix3x3
	{
	public:
		std::array<float, 9> elements; //vector to save the matrix's elements

		// Different ways of initializing a matrix
		Matrix3x3(bool identity = false);
		Matrix3x3(std::array<float, 9> _elements);
		~Matrix3x3() = default;

		void Print(); // Displays the matrix

		Vector3 Diagonal(); // method that returns the diagonal
		float Trace(); // method that returns the trace

		float operator[](int index); // operator to get any element of the matirx with the index

		void Opposite(); // returns the opposite of a matrix
		void Inverse();
		void Transpose(); // transposes a matrix and returns it
		void GaussJordan();
		float Determinant(); // returns the determinant of a matrix

		static Matrix3x3 Add(Matrix3x3 mat1, Matrix3x3 mat2); // adds two matrices
		static Matrix3x3 MultiplyNumber(Matrix3x3 mat, float number); // multiplies a matrix by a number
		static Matrix3x3 Multiply(Matrix3x3 mat1, Matrix3x3 mat2); // multiplies two matrices
		// returns a 3D rotation matrix with 3 rotation matrices for x, y and z axis
		static Matrix3x3 Rotation(float thetaX, float thetaY, float thetaZ);
		static Matrix3x3 RotationX(float thetaX);
		static Matrix3x3 RotationY(float thetaY);
		static Matrix3x3 RotationZ(float thetaZ);
	};


	Matrix3x3 operator+(const Matrix3x3& mat1, const Matrix3x3& mat2); // overloads + operator to add matrices
	Matrix3x3 operator-(const Matrix3x3& mat1, const Matrix3x3& mat2);
	Matrix3x3 operator*(const Matrix3x3& mat1, const Matrix3x3& mat2); // overloads * operator to multiply matrices
	Matrix3x3 operator*(const Matrix3x3& m, const float& f);
	Matrix3x3 operator*(const float& f, const Matrix3x3& m);
	Vector3 operator*(const Matrix3x3& m, const Vector3& v); // overloads * operator to multiply a matrix by a 3D vector
	Matrix3x3 operator+=(Matrix3x3& mat1, Matrix3x3& mat2);
	Matrix3x3 operator-=(Matrix3x3& mat1, Matrix3x3& mat2);
	Matrix3x3 operator*=(Matrix3x3& mat1, Matrix3x3& mat2);
	Matrix3x3 operator*=(Matrix3x3& m, float& f);

	// Class for 4x4 Matrices
	class Matrix4x4
	{
	public:
		std::array<float, 16> elements; //vector to save the matrix's elements

		// Different ways of initializing a matrix
		Matrix4x4(bool identity = false);
		Matrix4x4(std::array<float, 16> _elements);
		~Matrix4x4() = default;

		void Print(); // Displays the matrix

		Vector4 Diagonal(); // method that returns the diagonal
		float Trace(); // method that returns the trace

		float operator[](int index); // operator to get any element of the matirx with the index

		void Opposite(); // returns the opposite of a matrix
		void Inverse();
		void Transpose(); // transposes a matrix and returns it
		void GaussJordan();
		float Determinant(); // returns the determinant of a matrix
		Matrix4x4 Comatrix() const;

		static Matrix4x4 Homogeneous(Matrix3x3 m); // matrix 3x3 -> matrix 4x4
		static Matrix4x4 Add(Matrix4x4 mat1, Matrix4x4 mat2); // adds two matrices
		static Matrix4x4 MultiplyNumber(Matrix4x4 mat, float number); // multiplies a matrix by a number
		static Matrix4x4 Multiply(Matrix4x4 mat1, Matrix4x4 mat2); // multiplies two matrices
		static Matrix4x4 TRS(Vector3 translation, Vector3 rotation, Vector3 scaling); // returns a TRS matrix
		static Matrix4x4 View(Vector3 up, Vector3 center, Vector3 eye);
		static Matrix4x4 Perspective(float fovY, float aspect, float near, float far);
		static Matrix4x4 Orthographic(float top, float bottom, float right, float left, float far, float near);
	};

	Matrix4x4 operator+(const Matrix4x4& mat1, const Matrix4x4& mat2); // overloads + operator to add matrices
	Matrix4x4 operator-(const Matrix4x4& mat1, const Matrix4x4& mat2);
	Matrix4x4 operator*(const Matrix4x4& mat1, const Matrix4x4& mat2); // overloads * operator to multiply matrices
	Matrix4x4 operator*(const Matrix4x4& m, const float& f);
	Matrix4x4 operator*(const float& f, const Matrix4x4& m);
	Vector4 operator*(const Matrix4x4& m, const Vector4& v); // overloads * operator to multiply a matrix by a 4D vector
	Matrix4x4 operator+=(Matrix4x4& mat1, Matrix4x4& mat2);
	Matrix4x4 operator-=(Matrix4x4& mat1, Matrix4x4& mat2);
	Matrix4x4 operator*=(Matrix4x4& mat1, Matrix4x4& mat2);
	Matrix4x4 operator*=(Matrix4x4& m, float& f);
}