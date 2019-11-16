#pragma once

#include <vector>
#include <map>
#include <queue>

#include "node.h"
#include "filedata.h"

typedef std::priority_queue<Node, std::vector<Node>, std::greater<Node>> HuffmanQueue;

extern std::map<char, int> gCharRates;
extern std::map<char, std::string> gCodingTable;

extern HuffmanQueue huffmanQueue;

void countCharacters(FileData);
uint countNumberOfBits();

void createTree();
void createQueue(Node&);
void createTable();