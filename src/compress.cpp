#include "compress.h"

#include <string>
#include <iostream>
#include <bitset>
#include <fstream>

#include <math.h>

#include "filedata.h"
#include "huffman.h"

static FileData fd;
static std::ofstream compressedFile;

void compress(std::string fileName)
{    
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

void createTableSizeHeader()
{
    uint tableSize = gCodingTable.size();

    compressedFile.write((char*)&tableSize, sizeof(uint));
}

void createTableHeader()
{
    char encodingSize;
    char encodingChar;

    uint bytes;
    uint remainingNumOfBits;

    std::string encodingPiece;
    std::string encodingCopy;

    std::bitset<8> encoding;

    for (auto tableUnit : gCodingTable)
    {
        compressedFile.write(&tableUnit.first, sizeof(char));

        encodingSize = tableUnit.second.length();
        compressedFile.write(&encodingSize, sizeof(char));
        
        bytes = std::ceil(encodingSize / 8.0);

        encodingCopy = tableUnit.second;
        
        std::string zeros = "";

        for (uint i = 0; i < (bytes * 8) - (uint)encodingSize; i++)
        {
            zeros += "0";
        }

        encodingCopy = zeros + encodingCopy;

        for (uint i = 0; i < bytes; i++)
        {
            remainingNumOfBits = std::min((uint)8, (uint)encodingCopy.size());
            encodingPiece = encodingCopy.substr(0, remainingNumOfBits);

            encodingCopy.erase(0, remainingNumOfBits);
            
            encoding = std::bitset<8>(encodingPiece);

            encodingChar = encoding.to_ulong();

            compressedFile.write(&encodingChar, sizeof(char));
        }   
    }    
}

void createNumBitsHeader()
{
    ulong numOfBits = countNumberOfBits();

    compressedFile.write((char*)&numOfBits, sizeof(ulong));
}

void closeCompressedFile()
{
    compressedFile.close();
}

void writeBits(std::string bitString)
{
    char byteToWrite;

    std::bitset<8> bitsToWrite(bitString);

    byteToWrite = bitsToWrite.to_ulong();
    
    compressedFile.write(&byteToWrite, sizeof(char));
}

void createCodedString()
{
    std::string codedString = "";
    std::string codedChar = "";
  
    fd.reset();

    while (!fd.isFinished())
    {
        codedChar = gCodingTable[fd.getNextByte()];
        codedString += codedChar;

        while (codedString.length() >= 8)
        {
            writeBits(codedString.substr(0, 8));

            codedString.erase(0, 8);
        }
    }

    if (codedString.length() > 0)
    {
        uint size = codedString.size();

        for (uint i = 0; i < 8 - size; ++i)
        {
            codedString += "0";
        }
        
        writeBits(codedString);
    }
}

void createCompressedFile(std::string fileName)
{
    std::string compressedFileName = fileName + ".cmp";

    openCompressedFile(compressedFileName);

    createTableSizeHeader();
    createTableHeader();
    createNumBitsHeader();
        
    createCodedString();
    
    closeCompressedFile();
}