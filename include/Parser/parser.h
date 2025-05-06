#include <Lexer/LexemString.h>
#include "tree.h"
#include <vector>
#include <Lexer/Table.h>
#include <Lexer/Error.h>

class Parser{
private:
    Lexem TS;
    const LexemString& lexems; 
    const Tables &tables;
    int i;
public:
    Parser(const LexemString &Lexem_String, const Tables &tables);
    void SCN();
    Tree *generate_tree();
    Node *signal_program();
    Node *program();
    Node *procedure_identifier();
    Node *block();
    Node *declarations();
    Node *statements_list();
    Node *empty();
    Node *procedure_declarations();
    Node *procedure();
    Node *parameters_list();
    Node *declarations_list();
    Node *declaration();
    Node *variable_identifier();
    Node *identifiers_list();
    Node *attribute();
    Node *attributes_list();
    Node *identifier();
};