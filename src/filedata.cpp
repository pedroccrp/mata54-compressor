#include "filedata.h"

#include <iostream>
#include <algorithm>

#include <stdio.h>

FileData::FileData()
{
}

FileData::~FileData()
{
}

void FileData::open(std::string fileName)
{
    _fp = fopen(fileName.c_str(), "r");

    if (_fp == nullptr)
    {
        std::cerr << "Error while opening file!\n";
        exit(1);
    }

    fseek(_fp, 0, SEEK_END);
    _fileRemainSize = ftell(_fp);
    fseek(_fp, 0, SEEK_SET);
}


bool FileData::_readToBuffer()
{
    int amount = std::min(MAX_BUFFER_SIZE, _fileRemainSize);

    if (amount == 0)
    {
        return false;
    }

    try
    {
        _bufferSize = _bufferRemainSize = fread(&_buffer, 1, amount, _fp);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error reading file! " << e.what() << '\n';
    }
    
    return true;
}

void FileData::reset()
{
    fseek(_fp, 0, SEEK_SET);
    
    _fileRemainSize = _bufferRemainSize = 0;
}

char FileData::getNextByte()
{
    if (_bufferRemainSize == 0)
    {
        bool readResult = _readToBuffer();

        if (!readResult)
        {
            std::cerr << "Nothing to read on file!\n";
            exit(1);
        }
    }

    char byteToReturn = _buffer[_bufferSize - _bufferRemainSize];

    --_bufferRemainSize;
    --_fileRemainSize;

    return byteToReturn;
}

bool FileData::isFinished()
{
    return (_fileRemainSize == 0);
}

void FileData::close()
{
    if (_fp != nullptr)
    {
        fclose(_fp);
        _fp = nullptr;
    }    
}