#include "compress.h"

#include <iostream>

#include "filedata.h"

static FileData fd;

void compress(std::string fileName)
{
    std::cout << "Compressing...\n";
    
    fd.open(fileName);

    // To do

    fd.close();
}