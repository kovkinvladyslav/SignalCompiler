#include <Lexer/LexemString.h>

void LexemString::add(Lexem newLexem)
{
	lexemString.push_back(newLexem);
}

const std::vector<Lexem>& LexemString::get() const 
{
	return lexemString;
}

void LexemString::clear()
{
	lexemString.clear();
}

void LexemString::Output()
{
	if (lexemString.empty()) {
		std::printf("\nLA scan encountered no lexems.\n");
	}
	else {
		std::printf("\nLexem String:\n");
		std::printf("%10s%10s%10s%10s\n",
			"Line", "Column", "Code", "Lexem");

		for (auto lexem : lexemString) {
			std::printf("%10d%10d%10d%10s\n",
				lexem.nline, lexem.ncol, lexem.code, lexem.Lexem.c_str());
		}
	}
	
}
