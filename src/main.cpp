#include <iostream>
#include <string>

#include "compress.h"
#include "decompress.h"

int main(int argc, char const *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Missing parameters!\n";
        return 1;
    }

    std::string option = argv[1];
    std::string fileName = argv[2];

    if (option == "-c")
    {
        compress(fileName);
    }
    else if (option == "-d")
    {
        decompress(fileName);
    }
    else
    {
        std::cerr << "Invalid option!\n";
        return 1;
    }

    return 0;
}
