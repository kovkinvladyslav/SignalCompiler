#pragma once
#include <fstream>
#include <iostream>

#include "LexemString.h"
#include "Table.h"
#include "Attributes.h"
#include "Error.h"



class TSymbol {
public:
	char value;
	int attr;
};

class Token {
public:
	std::string lexem = "";
	int code = 0;
	void set(const std::string& token, int code);
};

class Position {
public:
	int column = 1;
	int line = 1;
};

class Lexer
{
private:
	std::ifstream infile;
	Tables& LexTable;
	Attributes& attributes;
	Position currPosition;
	bool OpenFile(const std::string& filename);

	LexemString scanResult;
public:
	bool scan(const std::string& filename);
	LexemString GetScanResult();
	Lexer(Tables& LexTable, Attributes& attributes);
	~Lexer();

	TSymbol Gets();
};

