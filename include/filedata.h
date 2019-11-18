#pragma once

#include <string>

#include <stdio.h>

#define MAX_BUFFER_SIZE 1

class FileData
{
private:
    FILE* _fp = nullptr;

    ulong _bufferSize = 0;
    ulong _bufferRemainSize = 0;
    ulong _fileSize = 0;
    ulong _fileRemainSize = 0;

    char _buffer[MAX_BUFFER_SIZE];

    bool _readToBuffer();

public:
    FileData();
    ~FileData();

    void open(std::string);
    void close();

    char getNextByte();
    bool isFinished();
    
    ulong getFileRemainSize();
    ulong getFileSize();
    void setFileSize(int);
    void reset();
    
    void readAmount(void*, uint, uint);
    void seek(uint);
    
};