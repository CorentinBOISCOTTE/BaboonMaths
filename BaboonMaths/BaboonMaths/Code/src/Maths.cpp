#include "BaboonMaths.h"

namespace Baboon
{
	float ToRadians(float deg)
	{
		return deg * (PI / 180.f);
	}

	float ToDegrees(float rad)
	{
		return rad * (180.f / PI);
	}
}
