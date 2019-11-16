#include "node.h"

Node::Node()
{
}

Node::Node(char value_, int rate_, bool isLeaf_)
{
    value = value_;
    rate = rate_;
    isLeaf = isLeaf_;
}

Node::~Node()
{
}

void Node::addChild(Node node)
{
    children.push_back(node);
}

bool operator<(const Node& n1, const Node& n2)
{
    return n1.rate < n2.rate;
}

bool operator>(const Node& n1, const Node& n2)
{
    return n1.rate > n2.rate;
}

bool operator==(const Node& n1, const Node& n2)
{
    return n1.rate == n2.rate;
}
