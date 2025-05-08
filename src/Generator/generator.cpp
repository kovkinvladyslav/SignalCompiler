#include <Generator/generator.h>
#include <iostream>
#include <string>
#include <Lexer/LexemString.h>
#include <algorithm>
#include <Lexer/Error.h>
#include <fstream>
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
    if(node->get_children()[2]->get_children()[0]->get_value() != "<empty>"){
        auto beginLexem = scan_result.find("BEGIN");
        errorLogger.logError("Generator", beginLexem.nline, beginLexem.ncol, "Statements list should be empty!");
    }
}

void Generator::generate_declarations(Node* node){
    auto procedure_declarations = node->get_children()[0]->get_children();
    emit("; Start of procedure declarations:");
    for(auto procedure : procedure_declarations){
        if(procedure->get_value() == "<procedure>"){
            generate_procedure(procedure);
        }
    }
    emit("; End of procedure declarations");
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
    emit(proc_identifier + ":");
    auto parameters = node->get_children()[2];
    generate_parameters_list(parameters);
    emit("; End of Procedure declaration: " + proc_identifier);
}

void Generator::generate_parameters_list(Node *node){
    if(node->get_children()[0]->get_value() == "<empty>"){
        return;
    }
    emit("; Start of parameters list");
    auto declaration_list = node->get_children()[1];


    generate_declarations_list(declaration_list);

}

void Generator::generate_declarations_list(Node *node) {
    if (node->get_value() == "<empty>" || node->get_children()[0]->get_value() == "<empty>") {
        return;
    }

    emit("; Start of declarations");

    std::vector<std::string> baseTypes = {"INTEGER", "FLOAT", "BLOCKFLOAT"};
    for (auto declaration : node->get_children()) {
        std::vector<std::string> variables;
        std::vector<std::string> typeAttrs;

        auto vars_nodes = declaration->get_children()[0];
        auto type_nodes = declaration->get_children()[2];

        for (auto var_node : vars_nodes->get_children()) {
            variables.push_back(var_node->get_children()[0]->get_children()[0]->get_value());
        }

        for (auto type_node : type_nodes->get_children()) {
            typeAttrs.push_back(type_node->get_children()[0]->get_children()[0]->get_value());
        }

        if (std::find(typeAttrs.begin(), typeAttrs.end(), "EXT") != typeAttrs.end()) {
            Lexem error_var = scan_result.find(variables[0]);
            errorLogger.logError("Generator", error_var.nline, error_var.ncol, "Attribute EXT can't be in parameters!");
            return;
        }

        std::string baseType;
        bool isComplex = false;
        bool isSignal = false;

        for (const auto& attr : typeAttrs) {
            if (std::find(baseTypes.begin(), baseTypes.end(), attr) != baseTypes.end()) {
                if (!baseType.empty()) {
                    Lexem error_var = scan_result.find(variables[0]);
                    errorLogger.logError("Generator", error_var.nline, error_var.ncol, "Parameter can have only one base type");
                    return;
                }
                baseType = attr;
            } else if (attr == "COMPLEX") {
                isComplex = true;
            } else if (attr == "SIGNAL") {
                isSignal = true;
            }
        }

        if (baseType.empty()) {
            Lexem error_var = scan_result.find(variables[0]);
            errorLogger.logError("Generator", error_var.nline, error_var.ncol, "Parameter must have one base type");
            return;
        }

        for (auto& var : variables) {
            generate_variable(var, baseType, isComplex, isSignal);
        }
    }
}


void Generator::generate_variable(std::string& var_name, std::string& baseType, bool isComplex, bool isSignal){
    if (baseType == "INTEGER") {
        if (isComplex) {
            generate_integer(var_name + "_RE");
            generate_integer(var_name + "_IM");
        } else {
            generate_integer(var_name);
        }
    } else if (baseType == "FLOAT") {
        if (isComplex) {
            generate_float(var_name + "_RE");
            generate_float(var_name + "_IM");
        } else {
            generate_float(var_name);
        }
    } else if (baseType == "BLOCKFLOAT") {
        if (isComplex) {
            generate_blockfloat(var_name + "_RE");
            generate_blockfloat(var_name + "_IM");
        } else {
            generate_blockfloat(var_name);
        }
    }

    if (isSignal) {
        generate_signal(var_name);
    }

}


void Generator::generate_integer(std::string var_name){
    emit("POP [VAR_" + var_name + "]");
}

void Generator::generate_float(std::string var_name){
    emit("POP [VAR_" + var_name + "_MANT]");
    emit("POP [VAR_" + var_name + "_EXP]");
}

void Generator::generate_blockfloat(std::string var_name){
    generate_integer(var_name + "_COMMON_EXP");
    for(int i = 0; i < 5; i++){
        generate_integer(var_name + "_MANT_" + std::to_string(i));
    }
}

void Generator::generate_signal(std::string var_name){
    emit("LINK [" + var_name + "]");
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

void Generator::write_listing(std::string filename){
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << listing.str();
        outFile.close();
        std::cout << "Listing File written successfully." << std::endl;
    } else {
        std::cerr << "Failed to open file." << std::endl;
    }

}