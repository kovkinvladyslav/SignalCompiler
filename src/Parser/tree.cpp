#include <Parser/tree.h>
#include <iostream>

Tree::Tree(Node *root_node)
:root(root_node)
{}

std::string Node::get_value() const {
    return value;
}

void Node::add_child(Node *newNode){
    if(newNode != nullptr){
        children.push_back(newNode);
    }
}

Node::Node(std::string new_value){
    value = new_value;
}

void Node::set_value(std::string new_value){
    value = new_value;
}

const std::vector<Node *> &Node::get_children() const {
    return children;
}

void output_tree_recursive(Node *root, std::string prefix = "", bool isLast = false){
    std::cout << prefix;

    std::cout << (!isLast ? "├──" : "└──" );
    prefix += isLast ? "    " : "│   ";

    std::cout << root->get_value() << std::endl;
    std::vector<Node *> children = root->get_children();
    int children_N = static_cast<int>(children.size());
    for(int i = 0; i < children_N; i++){
        output_tree_recursive(children[i], prefix, i >= children_N);
    }
}

void Tree::output_tree(){
    printf("\nTree:\n");
    output_tree_recursive(root);
}

Node *Tree::get_root(){
    return root;
}