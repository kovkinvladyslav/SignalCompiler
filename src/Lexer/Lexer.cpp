#include <Lexer/Lexer.h>


bool Lexer::OpenFile(const std::string& filename)
{
	infile.open(filename);
	
	return infile.is_open();
}

Lexer::~Lexer() {

}

TSymbol Lexer::Gets()
{
    TSymbol result;
    if (infile.get(result.value)) {
        result.attr = attributes.getCategory((unsigned char)result.value);
        if (result.value == '\n') {
            currPosition.column = 0;
            currPosition.line++;
        }
        else if (result.value == '\t') {
            currPosition.column += 4;
        }
        else {
            currPosition.column++;
        }
    } 
    else {
        result.value = '\0';
        result.attr = -1;
    }
    return result;
}

Lexer::Lexer(Tables& LexTable, Attributes& attributes)
    :LexTable(LexTable), attributes(attributes)
{

}


bool Lexer::scan(const std::string& filename)
{
	if (!OpenFile(filename)) {
        errorLogger.logError("Lexer", currPosition.line, currPosition.column, "Can't open file");
        return false;
	}
    scanResult.clear();
    currPosition = { 1, 1 };
    TSymbol symbol = Gets();

    while (!infile.eof()) {
        Position startOfToken = currPosition;
        std::string buff = "";
        Token token;
        bool SuppressOutput = false;
        int LexCode = -1;
        switch (symbol.attr)
        {
        case 0:
            while (!infile.eof()) {
                symbol = Gets();
                if (symbol.attr != 0) {
                    break;
                }
            }
            SuppressOutput = true;
            break;
        case 1:
            errorLogger.logError("Lexer", currPosition.line, currPosition.column, "Illegal constant '" + std::string(1, symbol.value) + "' detected.");
            symbol = Gets();
            return false;
            break;
        case 2:
            startOfToken = currPosition;
            while (!infile.eof() && (symbol.attr == 2 || symbol.attr == 1)) {
                buff.push_back(symbol.value);
                symbol = Gets();
            }
            LexCode = LexTable.Keywords.get(buff);
            if (LexCode == -1) {
                LexCode = LexTable.Identifiers.get(buff);
                if (LexCode == -1) {
                    LexCode = LexTable.Identifiers.append(buff);
                }
            }
            token.set(buff,LexCode);
            break;
        case 3:
            if (infile.eof()) {
                token.set("(", LexTable.Delimiters.get("("));
            }
            else {
                symbol = Gets();
                if (symbol.value == '*') {
                    if (infile.eof()) {
                        errorLogger.logError("Lexer", currPosition.line, currPosition.column, "Unterminated comment: expected '*)' but reached end of file.");
                        return false;
                    }
                    symbol = Gets();
                    do {
                        while (!infile.eof() && symbol.value != '*') {
                            symbol = Gets();
                        }
                        if (infile.eof()) {
                            errorLogger.logError("Lexer", startOfToken.line, startOfToken.column, "Unterminated comment: expected '*)' but reached end of file.");
                            symbol.value = '+';
                            symbol.attr = 6;
                            break;
                        }
                        symbol = Gets();
                    } while (symbol.value != ')');
                    SuppressOutput = true;
                    if (!infile.eof()) {
                        symbol = Gets();
                    }
                }
                else {
                    token.set("(", LexTable.Delimiters.get("("));
                }
            }
            break;

        case 4:
            token.set(std::string(1, symbol.value), LexTable.Delimiters.get(std::string(1, symbol.value)));
            symbol = Gets();
            break;
        case 6:
            errorLogger.logError("Lexer", currPosition.line, currPosition.column, "Illegal character '" + std::string(1, symbol.value) + "' detected.");
            symbol = Gets();
            return false;
            break;

        default:
            break;
        }
        if (!SuppressOutput) {
            scanResult.add({startOfToken.line, startOfToken.column, token.code, token.lexem});

        }
    }
    infile.close();
    return true;
}

LexemString Lexer::GetScanResult()
{
    return scanResult;
}



void Token::set(const std::string& token, int code)
{
    this->lexem = token;
    this->code = code;
}
