#include <Generator/generator.h>
#include <iostream>
#include <string>
#include <Lexer/LexemString.h>
#include <algorithm>

#include <Lexer/Error.h>

void Generator::generate_code(Tree *parser_tree){
    auto root = parser_tree->get_root();
    generate_program(root->get_children()[0]);
}

void Generator::generate_program(Node *node){
    auto procedure_identifier = node->get_children()[1];
    std::string program_name = procedure_identifier->get_children()[0]->get_children()[0]->get_value();
    emit("; Start of Program " + program_name); 
    auto block = node->get_children()[3];
    generate_block(block);
    emit("; End of Program " + program_name);
}

void Generator::generate_block(Node* node){
    auto declarations = node->get_children()[0];
    auto statements_list = node->get_children()[2];
    generate_declarations(declarations);
}

void Generator::generate_declarations(Node* node){
    auto procedure_declarations = node->get_children()[0]->get_children();
    emit("; Start of procedure declarations:");
    for(auto procedure : procedure_declarations){
        if(procedure->get_value() == "<procedure>"){
            generate_procedure(procedure);
        }
    }
}

void Generator::generate_procedure(Node* node){
    std::string proc_identifier = node->get_children()[1]->get_children()[0]->get_children()[0]->get_value();
    if(procedure_names.find(proc_identifier) != procedure_names.end()){
        Lexem proc_id_lex = scan_result.find(proc_identifier);
        errorLogger.logError("Generator", proc_id_lex.nline, proc_id_lex.ncol, "redefenitions of a procedures are not allowed ! (can't give two procedures same name)");
        return;
    } else {
        procedure_names.insert(proc_identifier);
    }
    emit("; Start of Procedure declaration: " + proc_identifier);
    auto parameters = node->get_children()[2];
    generate_parameters_list(parameters);
    emit("; End of Procedure declaration: " + proc_identifier);
}

void Generator::generate_parameters_list(Node *node){
    if(node->get_children()[0]->get_value() == "<empty>"){
        return;
    }
    emit("; Start of parameters list");
    std::vector<std::string> variables;
    std::vector<std::string> types;

    generate_declarations_list(node->get_children()[1]);

}


void Generator::generate_declarations_list(Node *node){
    if(node->get_value() == "<empty>"){
        return;
    }
    emit("; Start of declarations");
    //todo
}

void Generator::emit(const std::string& line){
    listing << line << "\n";
}

void Generator::output_listing(){
    std::cout << listing.str();
}

Generator::Generator(LexemString &scan_result)
:scan_result(scan_result)
{
    
}