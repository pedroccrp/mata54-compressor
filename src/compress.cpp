#include "compress.h"

#include <string>
#include <iostream>
#include <fstream>

#include "filedata.h"
#include "huffman.h"

static FileData fd;

void compress(std::string fileName)
{
    std::cout << "Compressing...\n";
    
    fd.open(fileName);

    countCharacters(fd);
    createTable();

    fd.close();

    createCompressedFile(fileName);
}

void createCompressedFile(std::string fileName)
{
    fileName += ".cmp";

    std::cout << "Writting compressed file...\n";
}