#pragma once

#include <vector>
#include <string>
#include <queue>
#include <ctime>
#include <iostream>
// number of children
static int n = 5;

//Citation: https://www.geeksforgeeks.org/insertion-in-n-ary-tree-in-given-order-and-level-order-traversal/
//Citation: https://www.geeksforgeeks.org/generic-treesn-array-trees/amp/
struct Node {
    double value;
    double value2;
    std::vector<Node*> less;
    std::vector<Node*> more;
    std::string name;

    Node(std::string nam, double val, double val2);

    void insert(std::string& nam, double val, double val2);

    // sorts a vector of nodes
    std::vector<Node*> sort(std::vector<Node*> children);
};

struct Tree {
    Node* root;

    Tree();

    void insert(std::string& nam, double val, double val2);
    void print();
    // finds all the elements with name nam in increasing or decreasing order
    std::vector<Node*> find(std::string& nam, bool sort);
    // finds all the elements with word nam in increasing or decreasing order
    std::vector<Node*> findKey(std::string& nam, bool sort);
};
