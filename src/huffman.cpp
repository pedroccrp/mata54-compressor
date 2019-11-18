#include "huffman.h"

#include <iostream>
#include <map>
#include <bitset>
#include <queue>

#include <math.h>

#include "filedata.h"

std::map<char, ulong> gCharRates;
std::map<char, std::string> gCodingTable;
std::map<std::string, char> gDecodingTable;

HuffmanQueue huffmanQueue;

void countCharacters(FileData fd)
{
    while (!fd.isFinished())
    {
        gCharRates[fd.getNextByte()]++;
    }    
}

ulong countNumberOfBits()
{
    ulong numberOfBits = 0;

    for (auto charRate : gCharRates)
    {
        numberOfBits += charRate.second * gCodingTable[charRate.first].length(); 
    }

    return numberOfBits;
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

void mountTable(FileData& fd)
{
    uint tableSize = 0;
    
    char id;
    uint encodeSize;
    uint encodeBytes;
    
    std::string encode;
    std::string parsedEncode;

    fd.readAmount(&tableSize, sizeof(uint), 1);

    for (uint i = 0; i < tableSize; i++)
    {
        id = fd.getNextByte();

        encodeSize = fd.getNextByte();
        encodeBytes = std::ceil(encodeSize / 8.0);
        
        encode = "";

        for (uint i = 0; i < encodeBytes; i++)
        {
            encode += std::bitset<8>(fd.getNextByte()).to_string();
        }

        parsedEncode = encode.substr((encodeBytes * 8) - encodeSize, encodeSize);
        
        gDecodingTable[parsedEncode] = id;
    }
}