//------------------------------------------------------------------------------
//
// File Name:	Trace.cpp
// Author(s):	Michael Howard (michael.howard)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------


#include "Trace.h"

#define UNREFERENCED_PARAMETER(P) (P)

Trace::Trace()
{
	traceFile.open(traceFileName);

	if (!traceFile.is_open())
	{
		std::cout << traceFileName << " open failed" << std::endl;
	}
	else
	{
		std::cout << traceFileName << " open succeeded" << std::endl;
	}
}
// Shutdown the Tracing/Logging module.
Trace::~Trace()
{
	if (traceFile.is_open())
		traceFile.close();

}


void Trace::TraceMessage(const char* formatString, ...)
{
	UNREFERENCED_PARAMETER(formatString);

	va_list arg_ptr;

	// Verify that the traceStream is valid.
	if (traceFile.is_open())
	{
		va_start(arg_ptr, formatString);
		traceFile << formatString << arg_ptr << std::endl;
		va_end(arg_ptr);
	}
}


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

