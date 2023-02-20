//------------------------------------------------------------------------------
//
// File Name:	Tracing.h
// Author(s):	Michael Howard (michael.howard)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#pragma once
#include <fstream>
#include <iostream>
#include <stdarg.h>

class Trace
{
public:
	Trace();
	~Trace();
	void TraceMessage(const char* formatString, ...);
private:
	std::string traceFileName = "Trace.log";
	std::ofstream traceFile;
};