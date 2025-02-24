#include "BaboonMaths.h"
using namespace Baboon;

int main()
{
	Matrix4x4 m({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,11, 12, 13 ,14 ,15 });
	m.Print();
	m.Transpose();
	m.Print();

	return 1;
}