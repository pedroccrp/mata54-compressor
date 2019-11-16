#include "huffman.h"

#include <iostream>
#include <map>
#include <queue>

#include "filedata.h"

std::map<char, int> gCharRates;
std::map<char, std::string> gCodingTable;

HuffmanQueue huffmanQueue;

void countCharacters(FileData fd)
{
    while (!fd.isFinished())
    {
        gCharRates[fd.getNextByte()]++;
    }    
}

void createTree()
{
    for (auto charRate : gCharRates)
    {
        huffmanQueue.push(Node(charRate.first, charRate.second, true));
    }
}

void createQueue(Node& root)
{
    Node firstNode;
    Node secondNode;
    Node insertNode;

    while (!huffmanQueue.empty())
    {
        if (huffmanQueue.size() == 1)
        {
            root = huffmanQueue.top();
            huffmanQueue.pop();
            break;
        }

        firstNode = huffmanQueue.top();
        huffmanQueue.pop();

        secondNode = huffmanQueue.top();
        huffmanQueue.pop();

        insertNode = Node(' ', (firstNode.rate + secondNode.rate), false);
        insertNode.addChild(firstNode);
        insertNode.addChild(secondNode);

        huffmanQueue.push(insertNode);
    }
}

void fillTable(Node& currentNode, std::string currentCoding)
{
    if (currentNode.isLeaf)
    {
        gCodingTable[currentNode.value] = currentCoding;
    }
    else
    {
        fillTable(currentNode.children[0], currentCoding + "0");
        fillTable(currentNode.children[1], currentCoding + "1");
    }    
}

void createTable()
{
    Node root;

    std::cout << "Creating table...\n";

    createTree();
    createQueue(root);
    
    if (root.isLeaf)
    {
        gCodingTable[root.value] = "0";
    }
    else
    {
        fillTable(root, "");
    }
}