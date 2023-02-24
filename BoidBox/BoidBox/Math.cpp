//------------------------------------------------------------------------------
//
// File Name:	Math.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include "Math.h"
#include <math.h>

#ifndef MATH_CPP
#define MATH_CPP

template<typename T>
T Clamp(const T& val, const T& min, const T& max)
{
	if (val < min)
		return min;
	if (val > max)
		return max;
	return val;
}

template <typename T>
T Lerp(const T& start, const T& end, float interpolation)
{
	Clamp(interpolation, 0.0f, 1.0f);
	return start + ((end - start) * interpolation);
}
#endif // !MATH_CPP

