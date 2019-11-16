#include "compress.h"

#include <string>
#include <iostream>
#include <bitset>
#include <fstream>

#include "filedata.h"
#include "huffman.h"

static FileData fd;
static std::ofstream compressedFile;

std::string codedString;

void compress(std::string fileName)
{
    std::cout << "Compressing...\n";
    
    fd.open(fileName);

    countCharacters(fd);
    createTable();
    createCompressedFile(fileName);

    fd.close();
}

void openCompressedFile(std::string compressedFileName)
{
    compressedFile = std::ofstream(compressedFileName);
}

void createNumberOfBitsHeader()
{
    uint numberOfBits = countNumberOfBits();
    
    compressedFile.write((char*)&numberOfBits, sizeof(uint));
}

void createTableHeader()
{
    std::bitset<8> encoding;
    std::string bits;

    for (auto tableUnit : gCodingTable)
    {
        compressedFile.write(&tableUnit.first, sizeof(char));

        bits = "";

        for (uint i = 0; i < (8 - tableUnit.second.length()); ++i)
        {
            bits += "0";
        }

        bits += tableUnit.second;

        encoding = std::bitset<8>(bits);
        
        compressedFile << encoding.to_ulong();
    }    
}

void closeCompressedFile()
{
    compressedFile.close();
}

void writeBits(std::string bitString)
{
    char byteToWrite;

    std::bitset<8> bitsToWrite;

    while (!bitString.empty())
    {
        bitsToWrite = std::bitset<8>(bitString.substr(0, 8));
        
        byteToWrite = bitsToWrite.to_ulong();

        compressedFile << byteToWrite;

        bitString.erase(0, 8);
    }
}

void createCodedString()
{
    codedString = "";
  
    fd.reset();

    while (!fd.isFinished())
    {
        codedString += gCodingTable[fd.getNextByte()];

        while (codedString.length() >= BITS_TO_WRITE)
        {
            writeBits(codedString.substr(0, BITS_TO_WRITE));

            codedString.erase(0, BITS_TO_WRITE);
        }
    }

    if (codedString.length() > 0)
    {
        writeBits(codedString);
    }
}

void createCompressedFile(std::string fileName)
{
    std::string compressedFileName = fileName + ".cmp";

    std::cout << "Writting compressed file...\n";

    openCompressedFile(compressedFileName);

    createNumberOfBitsHeader();
    createCodedString();
    createTableHeader();
    
    closeCompressedFile();
}