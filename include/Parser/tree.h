#pragma once
#include <vector>
#include <string>
class Node{
    std::vector<Node*> children;
    std::string value;
    public:
    Node(std::string new_value);
    void add_child(Node *newNode);
    void set_value(std::string new_value);
    std::string get_value() const;
    const std::vector<Node*> &get_children() const;
};

class Tree{
    Node* root;
    public:
    Tree(Node *root_node);
    Node *get_root();
    void output_tree();
};
