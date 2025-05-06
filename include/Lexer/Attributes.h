#pragma once
class Attributes
{
private:
	unsigned char SymbolCategories[256];
public:
	int getCategory(unsigned char symbol);
	Attributes();
};

