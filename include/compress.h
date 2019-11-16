#pragma once

#include <string>

#define BYTES_TO_WRITE 2
#define BITS_TO_WRITE 8 * BYTES_TO_WRITE

extern std::string codedString;

void compress(std::string);

void openCompressedFile(std::string);
void createNumberOfBitsHeader();
void createTableHeader();
void closeCompressedFile();

void writeBits(std::string);

void createCodedString();
void createCompressedFile(std::string);