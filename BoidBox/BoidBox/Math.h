//------------------------------------------------------------------------------
//
// File Name:	Math.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#ifndef MATH_H
#define MATH_H

template<typename T>
T Clamp(const T& val, const T& min = 0, const T& max = 1);

template<typename T>
T Lerp(T& start, T& end, float interpolation);

#include "Math.cpp"

#endif