#pragma once
#ifndef BINARY_FILE_STREAM_H
#define BINARY_FILE_STREAM_H

#include "BinaryStream.h"
#include <iostream>
#include <memory.h>

namespace XStream
{
    /*
        @. 二进制文件头
    */
    typedef struct tagBinaryFileHeader
    {
        char szTag[2];
        //数据长度
        int nDataLen;
        //保留
        char szReserve[58];

        tagBinaryFileHeader()
        {
            szTag[0] = 'B';
            szTag[1] = 'S';
            memset(&nDataLen, 0, sizeof(nDataLen));
            memset(szReserve, 0, sizeof(szReserve));
        }
    }BinaryFileHeader;

    /*
        @. 文件流
    */
    class UTILITY_EXPORT BinaryFileStream
    {
    public:
        BinaryFileStream(BinaryStream& refSteam, const std::string& filePath);
        ~BinaryFileStream();

        void setFilePath(const std::string& filePath);
        std::string filePath() const;

        void saveToFile();

        void readFromFile();
    protected:

        /*
            @. 从istream中读取文件头
        */
        bool __readHeader(std::istream& is);

        /*
            @. 通过mStreamRef流写入文件头结构
        */
        bool __writeHeader(std::ostream& os);
    protected:
        BinaryStream& mStreamRef;
        std::string mFilePath;
        BinaryFileHeader mFileHeader;
    };
}
#endif
