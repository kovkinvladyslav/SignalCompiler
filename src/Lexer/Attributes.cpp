#include <Lexer/Attributes.h>

int Attributes::getCategory(unsigned char symbol)
{
	return SymbolCategories[static_cast<int>(symbol)];
}

Attributes::Attributes()
{
    for (int i = 0; i < 256; i++) {
        SymbolCategories[i] = 6;
    }

    SymbolCategories[' '] = 0;
    SymbolCategories['\n'] = 0;
    SymbolCategories['\t'] = 0;

    for (char c = '0'; c <= '9'; c++) {
        SymbolCategories[(unsigned char)c] = 1;
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        SymbolCategories[(unsigned char)c] = 2;
    }

    SymbolCategories[';'] = 4;
    SymbolCategories[','] = 4;
    SymbolCategories[':'] = 4;
    SymbolCategories[')'] = 4;

    SymbolCategories['('] = 3;
}
