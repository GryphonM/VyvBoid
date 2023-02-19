//------------------------------------------------------------------------------
//
// File Name:	Stream.h
// Description:	Contains classes that handle reading (and writing?) data to and from files
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#pragma once
#include <string>
#include <fstream>

class TextStream
{
public:
	TextStream(std::string filename);
	TextStream(const char * filename);
	~TextStream();

	std::string ReadWord();
	void ReadWord(char* val);
	char ReadChar();
	int ReadInt();
	float ReadFloat();
	bool ReadBool(bool isAlpha = false);
	bool EndOfFile();
private:
	std::ifstream file;
};

class ReadCsv
{

};
