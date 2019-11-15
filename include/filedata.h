#pragma once

#include <string>

#include <stdio.h>

#define MAX_BUFFER_SIZE 1

class FileData
{
private:
    FILE* _fp = nullptr;

    int _bufferSize = 0;
    int _bufferRemainSize = 0;
    int _fileRemainSize = 0;

    char _buffer[MAX_BUFFER_SIZE];

    bool _readToBuffer();

public:
    FileData();
    ~FileData();

    void open(std::string);
    bool isFinished();
    char getNextByte();
    void close();
};