#include "decompress.h"

#include <iostream>

#include "filedata.h"

static FileData fd;

void decompress(std::string fileName)
{
    std::cout << "Decompressing...\n";

    fd.open(fileName);

    // To do

    fd.close();
}