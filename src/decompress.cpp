#include "decompress.h"

#include <iostream>
#include <fstream>
#include <bitset>

#include "huffman.h"
#include "filedata.h"

static FileData fd;

static std::ofstream decompressedFile;

void decompress(std::string fileName)
{
    fd.open(fileName);

    mountTable(fd);

    createDecompressedFile(fileName.substr(0, fileName.size() - 4));
    // createDecompressedFile(fileName + ".dec");

    fd.close();
}

void openDecompressedFile(std::string decompressedFileName)
{
    decompressedFile = std::ofstream(decompressedFileName);
}

void closeDecompressedFile()
{
    decompressedFile.close();
}

void createDecompressedFile(std::string decompressedFileName)
{
    ulong numOfBits = 0;

    std::string encode = "";
    
    std::string bits;

    fd.readAmount(&numOfBits, sizeof(ulong), 1);

    openDecompressedFile(decompressedFileName);

    while (!fd.isFinished() && numOfBits > 0)
    {
        bits = std::bitset<8>(fd.getNextByte()).to_string();

        for (size_t i = 0; i < 8; i++)
        {
            if (numOfBits <= 0)
            {
                break;
            }

            encode += bits[i];      

            if (gDecodingTable.count(encode))
            {
                decompressedFile.write(&gDecodingTable[encode], sizeof(char));
                encode = "";
            }

            --numOfBits;
        }        
    }    

    closeDecompressedFile();
}