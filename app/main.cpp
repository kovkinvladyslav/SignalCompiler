#include <iostream>
#include <fstream>
#include <error.h>

#include <Lexer/Lexer.h>
#include <Lexer/Table.h>
#include <Lexer/LexemString.h>
#include <Parser/parser.h>
#include <Lexer/Error.h>
#include <Generator/generator.h>
int main(int argc, char** argv){

    // if(argc != 2){
    //     std::cerr << "Compilation error: Path of file is required!";
    //     return 1;
    // }
    // std::string testPath = "./source/tests/";
    // std::string testFile = argv[1];

    // if (testFile.find('/') == std::string::npos) {
    //     testFile = testPath + testFile;
    // }
    std::string testFile = "../../tests/trueTest1.txt";

    Tables LexTable;
    Attributes attributes;
    Lexer lexer(LexTable, attributes);
    lexer.scan(testFile);
    LexemString scan_result = lexer.GetScanResult();
    scan_result.Output();
    LexTable.OutputAllTables();
    Parser parser(scan_result, LexTable);
    auto generated_Tree = parser.generate_tree();
    generated_Tree->output_tree();
    Generator gen(scan_result);
    gen.generate_code(generated_Tree);
    gen.output_listing();
    errorLogger.printErrors();
    

}