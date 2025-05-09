#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

#include <Lexer/Lexer.h>
#include <Lexer/Table.h>
#include <Lexer/LexemString.h>
#include <Parser/parser.h>
#include <Lexer/Error.h>
#include <Generator/generator.h>

int main() {
    std::vector<std::string> testFiles = {
        "../../tests/trueTest1.txt",
        "../../tests/trueTest2.txt",
        "../../tests/falseTest1.txt",
        "../../tests/falseTest2.txt",
        "../../tests/falseTest3.txt",
        "../../tests/falseTest4.txt"
    };

    while (true) {
        std::cout << "\nSelect a test file to compile:\n";
        for (size_t i = 0; i < testFiles.size(); ++i) {
            std::cout << i + 1 << ". " << testFiles[i] << "\n";
        }
        std::cout << "0. Exit\n";

        std::cout << "Enter the number of your choice: ";
        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очищення буфера
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 0) {
            std::cout << "Exiting.\n";
            break;
        }

        if (choice < 1 || choice > static_cast<int>(testFiles.size())) {
            std::cout << "Invalid selection. Try again.\n";
            continue;
        }

        std::string testFile = testFiles[choice - 1];
        std::cout << "\nCompiling file: " << testFile << "\n";

        Tables LexTable;
        Attributes attributes;
        Lexer lexer(LexTable, attributes);
        lexer.scan(testFile);

        LexemString scan_result = lexer.GetScanResult();
        scan_result.Output();
        LexTable.OutputAllTables();
        
        if(!errorLogger.hasErrors()){
            Parser parser(scan_result, LexTable);
            auto generated_Tree = parser.generate_tree();
            generated_Tree->output_tree();
            Generator gen(scan_result);
            if(!errorLogger.hasErrors()){
                gen.generate_code(generated_Tree);
                gen.output_listing();
                gen.write_listing("../../output.txt");
            }
        }       

        errorLogger.printErrors();

        std::cout << "\n--- Compilation finished ---\n";
        errorLogger.clear();
    }

    return 0;
}
