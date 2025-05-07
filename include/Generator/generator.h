#pragma once

#include <Parser/tree.h>
#include <string>
#include <sstream>
#include <set>
#include <Lexer/LexemString.h>

class Generator{
    private:
    std::ostringstream listing; 
    void emit(const std::string& line);
    void generate_block(Node* node);
    void generate_program(Node *node);
    void generate_declarations(Node *node);
    void generate_procedure(Node *node);
    void generate_parameters_list(Node *node);
    void generate_parameters_list(Node *node);

    std::set<std::string> procedure_names;
    LexemString &scan_result;

    public:
    Generator(LexemString &scan_result);
    void generate_code(Tree *parser_tree);
    void output_listing();
    void write_listing(std::string filename);
};