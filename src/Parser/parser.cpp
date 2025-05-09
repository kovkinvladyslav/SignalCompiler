#include <Parser/parser.h>

Parser::Parser(const LexemString &Lexem_String, const Tables &tables)
    : lexems(Lexem_String), tables(tables), i(0)
{

}

Tree *Parser::generate_tree(){
    SCN();
    Tree *result_tree = new Tree(signal_program());
    return result_tree;
}

void Parser::SCN(){
    if(i <  static_cast<int>(lexems.get().size())){
        TS = lexems.get()[i++];
    }
}

Node* Parser::signal_program(){
    Node *signal_program = new Node("<signal-program>");
    signal_program->add_child(program());
    return signal_program;
}

Node* Parser::program(){
    Node *program = new Node("<program>");

    if(TS.code != tables.Keywords.get("PROGRAM")){
        errorLogger.logError("Parser", TS.nline, TS.ncol, "Program should start with 'PROGRAM' keyword");
        program->add_child(new Node("<error>"));
        return program;
    } else {
        program->add_child(new Node(TS.Lexem));
    }
    SCN();
    program->add_child(procedure_identifier());
    if(program->get_children().size() == 0){
        errorLogger.logError("Parser", TS.nline, TS.ncol, "Expected program identifier");
        program->add_child(new Node("<error>"));
        return program;
    }
    SCN();
    if(TS.code != tables.Delimiters.get(";")){
        errorLogger.logError("Parser", TS.nline, TS.ncol, "Expected ';' after program identifier");
        program->add_child(new Node("<error>"));
        return program;
    } else {
        program->add_child(new Node(TS.Lexem));
    }
    SCN();
    program->add_child(block());
    
    SCN();
    if(TS.code != tables.Delimiters.get(";")){
        errorLogger.logError("Parser", TS.nline, TS.ncol, "Expected ';' after the block");
        program->add_child(new Node("<error>"));
        return program;
    } else {
        program->add_child(new Node(TS.Lexem));
        return program;
    }
    return program;
}

Node *Parser::identifier(){
    Node* identifier = new Node("<identifier>");
    if(TS.code != tables.Identifiers.get(TS.Lexem)){
        return nullptr;
    }

    identifier->add_child(new Node(TS.Lexem));
    return identifier;
}

Node *Parser::block(){
    Node *block = new Node("<block>");
    block->add_child(declarations());
    if(TS.code != tables.Keywords.get("BEGIN")){
        errorLogger.logError("Parser", TS.nline, TS.ncol, "Expected 'BEGIN' keyword");
        block->add_child(new Node("<error>"));
        return block;
    } else {
        block->add_child(new Node(TS.Lexem));
    }
    SCN();
    block->add_child(statements_list());
    if(TS.code != tables.Keywords.get("END")){
        errorLogger.logError("Parser", TS.nline, TS.ncol, "Expected 'END' keyword");
        block->add_child(new Node("<error>"));
        return block;
    } else {
        block->add_child(new Node(TS.Lexem));
    }
    return block;
}

Node *Parser::declarations(){
    Node* declarations = new Node("<declarations>");
    declarations->add_child(procedure_declarations());
    return declarations;
}

Node *Parser::procedure_declarations() {
    Node *procedure_declarations_node = new Node ("<procedure_declarations>");
    if(TS.code == tables.Keywords.get("BEGIN")){
        procedure_declarations_node->add_child(empty());
        return procedure_declarations_node;
    }
    procedure_declarations_node->add_child(procedure());
    while(TS.code == tables.Delimiters.get(";")){
        SCN();
        if(TS.code != tables.Keywords.get("BEGIN")){
            procedure_declarations_node->add_child(procedure());
        }
    }
    return procedure_declarations_node;
}

Node *Parser::procedure(){
    Node *procedure_node = new Node ("<procedure>");
    if(TS.code != tables.Keywords.get("PROCEDURE")){
        errorLogger.logError("Parser", TS.nline, TS.ncol, "Expected 'PROCEDURE' keyword");
        procedure_node->add_child(new Node("<error>"));
        return procedure_node;
    } else {
        procedure_node->add_child(new Node(TS.Lexem));
    }
    SCN();
    procedure_node->add_child(procedure_identifier());
    SCN();
    procedure_node->add_child(parameters_list());
    if(TS.code != tables.Delimiters.get(";")){
        errorLogger.logError("Parser", TS.nline, TS.ncol, "Expected ending ';' after procedure declaration");
        procedure_node->add_child(new Node("<error>"));
        return procedure_node;
    } else {
        procedure_node->add_child(new Node(";"));
    }
    return procedure_node;
}

Node *Parser::parameters_list(){
    Node *parameters_list_node = new Node ("<parameters-list>");
    if(TS.code != tables.Delimiters.get("(")){
        parameters_list_node->add_child(empty());
        return parameters_list_node;
    } else {
        parameters_list_node->add_child(new Node(TS.Lexem));
    }
    SCN();
    parameters_list_node->add_child(declarations_list());
    if(TS.code != tables.Delimiters.get(")")){
        errorLogger.logError("Parser", TS.nline, TS.ncol, "Expected '(' after parameters list");
        parameters_list_node->add_child(new Node("<error>"));
        return parameters_list_node;
    } else {
        parameters_list_node->add_child(new Node(TS.Lexem));
    }
    SCN();
    return parameters_list_node;
}

Node *Parser::declarations_list(){
    Node *declaration_list_node = new Node ("<declarations-list>");
    if(TS.code == tables.Delimiters.get(")")){
        declaration_list_node->add_child(empty());
        return declaration_list_node;
    }
    declaration_list_node->add_child(declaration());
    while(TS.code == tables.Delimiters.get(";")){
        SCN(); 
        if(TS.code != tables.Delimiters.get(")")){
            declaration_list_node->add_child(declaration());
        }
    }
    return declaration_list_node;
}

Node *Parser::declaration(){
    Node *declaration_node = new Node ("<declaration>");
    declaration_node->add_child(identifiers_list());
    if(TS.code != tables.Delimiters.get(":")){
        errorLogger.logError("Parser", TS.nline, TS.ncol, "Expected ':' between variables identifiers and attributes");
        declaration_node->add_child(new Node("<error>"));
        return declaration_node;
    } else {
        declaration_node->add_child(new Node(TS.Lexem));
    }
   declaration_node->add_child(attributes_list());
    if(TS.code != tables.Delimiters.get(";")){
        errorLogger.logError("Parser", TS.nline, TS.ncol, "Expected ';' in the end of declaration");
        declaration_node->add_child(new Node("<error>"));
        return declaration_node;
    } else {
        declaration_node->add_child(new Node (TS.Lexem));
    }
    return declaration_node;
}

Node *Parser::identifiers_list(){
    Node *identifiers_list_node = new Node("<identifiers-list>");
    identifiers_list_node->add_child(variable_identifier());
    SCN();
    while(TS.code == tables.Delimiters.get(",")){
        SCN();
        identifiers_list_node->add_child(variable_identifier());
        SCN();
    }
    return identifiers_list_node;
}

Node *Parser::attributes_list(){
    Node *attributes_list_node = new Node("<attributes-list>");
    SCN();
    attributes_list_node->add_child(attribute());
    SCN();
    while(TS.code != tables.Delimiters.get(";")){
        attributes_list_node->add_child(attribute());
        SCN();
    }
    return attributes_list_node;
}

Node *Parser::variable_identifier(){
    Node* variable_identifier_node = new Node ("<variable-identifier>");
    Node *identifier_node = identifier();
    if(identifier_node == nullptr){
        errorLogger.logError("Parser", TS.nline, TS.ncol, "Variable identifier is explected to be an identifier");
        variable_identifier_node->add_child(new Node("<error>"));
        return variable_identifier_node;
    } else {
        variable_identifier_node->add_child(identifier_node);
    }
    return variable_identifier_node;
}



Node *Parser::attribute(){
    Node* attribute_node = new Node ("<attribute>");
    Node *identifier_node = identifier();
    if(identifier_node == nullptr || TS.code > 1006){
        errorLogger.logError("Parser", TS.nline, TS.ncol, "Attribute name is explected to be type");
        attribute_node->add_child(new Node("<error>"));
        return attribute_node;
    } else {
        attribute_node->add_child(identifier_node);
    }
    return attribute_node;
}

Node *Parser::procedure_identifier(){
    Node *procedure_identifier = new Node ("<procedure-identifier>");
    Node *identifier_node = identifier();
    if(identifier_node == nullptr){
        errorLogger.logError("Parser", TS.nline, TS.ncol, "Procedure identifier is explected to be an identifier");
        procedure_identifier->add_child(new Node("<error>"));
        return procedure_identifier;
    } else {
        procedure_identifier->add_child(identifier_node);
    }
    return procedure_identifier;
}

Node *Parser::statements_list(){
    Node *statements_list_node = new Node("<statements-list>");
    statements_list_node->add_child(empty());
    return statements_list_node;
}

Node *Parser::empty(){
    Node *empty = new Node("<empty>");
    return empty;
}