#include "compress.h"

#include <iostream>

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
}