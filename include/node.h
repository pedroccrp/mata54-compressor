#pragma once

#include <vector>
#include <string>

class Node
{
private:

public:
    char value;
    int rate;
    bool isLeaf;
    std::vector<Node> children;

    Node();
    Node(char, int, bool);
    ~Node();

    void addChild(Node);
};

bool operator<(const Node&, const Node&);

bool operator>(const Node&, const Node&);

bool operator==(const Node&, const Node&);